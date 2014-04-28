package com.l0uy.phonegap;

import java.util.LinkedList;

import octoshape.osa2.Problem;
import octoshape.osa2.StreamPlayer;
import octoshape.osa2.android.OctoshapeSystem;
import octoshape.osa2.listeners.ProblemListener;
import octoshape.osa2.listeners.StreamPlayerListener;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.ActivityInfo;
import android.graphics.Point;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnVideoSizeChangedListener;
import android.net.Uri;
import android.os.Build;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.SurfaceHolder.Callback;
import android.view.WindowManager.LayoutParams;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.octoshape.android.client.OctoshapePortListener;
import com.octoshape.android.client.OctoStatic;


public class PGOctoShape extends CordovaPlugin {
	private static final String LOG_TAG = "PGOctoShape";
	
	private OctoshapeSystem os;
	private MediaPlayer mMediaPlayer;
	private StreamPlayer mStreamPlayer;

	private LinkedList<Uri> urlQueue = new LinkedList<Uri>();

	private SurfaceView mSurface;
	private Dialog dialog;
    
    private static final String ERROR_EVENT = "error";
    private static final String START_EVENT = "start";
    private static final String STOP_EVENT = "stop";

    private CallbackContext callbackContext;
    
    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
    	super.initialize(cordova, webView);
    	initOctoshapeSystem();
    }
    
    @Override
	public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
		Log.d(LOG_TAG, "execute: " + action);
    	if (action.equals("init")) {
            this.callbackContext = callbackContext;
    		return true;
    	} else if( action.equals("play") ) {
    		String OctoLink = args.optString(0);
    		
			mStreamPlayer = setupStream(OctoLink);
			mStreamPlayer.requestPlay();

	        try {
	            JSONObject obj = new JSONObject();
	            obj.put("type", START_EVENT);
	            obj.put("link", OctoLink);

	            sendUpdate(obj, false);
	        } catch (JSONException e) {
	            Log.d(LOG_TAG, "Should never happen");
	        }

			openDialog();
			
    		return true;
    	} else if( action.equals("stop") ) {
        	if( dialog != null ) {
        		dialog.dismiss();
            	closePlayer();
        		return true;
        	}
    		return false;
    	} else {
    		return false;
    	}
	}
    
    @Override
    public void onPause(boolean multitasking) {
    	if( dialog != null ) {
    		dialog.dismiss();
    	}
    	closePlayer();
    }
    @Override
    public void onDestroy() {
    	closePlayer();
		OctoStatic.terminate(null);
    }

	/**
	 * Creating OctoshapeSystem, adding ProblemListener for which we set to the
	 * language of the OS and setting OctoshapePortListener triggering a
	 * callback once the Octoshape service/client has started successfully.
	 */
	public void initOctoshapeSystem() {
		// Create OctoshapeSystem
		os = OctoStatic.create(cordova.getActivity(), problemListener,
				new OctoshapePortListener() {
					@Override
					public void onPortBound(int port) {
						Log.d(LOG_TAG, "onPortBound: " + port);
					}
				});
		
		// Adding AndroidMediaPlayer
		os.addPlayerNameAndVersion(OctoshapeSystem.MEDIA_PLAYER_NATIVE, OctoshapeSystem.MEDIA_PLAYER_NATIVE,
				"" + Build.VERSION.SDK_INT);
		
		// Launching OctoshapeSystem
		os.open();
	}
	
	protected void openDialog() {
		Log.d( LOG_TAG, "openDialog" );

        // Create dialog in new thread
        Runnable runnable = new Runnable() {
            public void run() {
	            cordova.getActivity().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
	            
		        dialog = new Dialog(cordova.getActivity(), android.R.style.Theme_NoTitleBar);
		        dialog.getWindow().getAttributes().windowAnimations = android.R.style.Animation_Dialog;
		        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
		        dialog.setCancelable(true);
		        dialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
		                public void onDismiss(DialogInterface dialog) {
		                	closePlayer();
		                	
		                    try {
		                        JSONObject obj = new JSONObject();
		                        obj.put("type", STOP_EVENT);
		
		                        sendUpdate(obj, false);
		                    } catch (JSONException e) {
		                        Log.d(LOG_TAG, "Should never happen");
		                    }

		                	cordova.getActivity().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED);
		                }
		        });
		        
		        dialog.getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            	dialog.getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
            	
		        // Main container layout
		        RelativeLayout main = new RelativeLayout(cordova.getActivity());
		        
				mSurface = new SurfaceView(cordova.getActivity());
				mSurface.setLayoutParams(new RelativeLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
				mSurface.setZOrderOnTop(true);
		        main.addView(mSurface);
		        
		        final ProgressBar loadingIndicator = new ProgressBar(cordova.getActivity());
		        loadingIndicator.setIndeterminate(true);
		        RelativeLayout.LayoutParams lilp = new RelativeLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		        lilp.addRule(RelativeLayout.CENTER_HORIZONTAL);
		        lilp.addRule(RelativeLayout.CENTER_VERTICAL);
		        loadingIndicator.setLayoutParams(lilp);
		        main.addView(loadingIndicator);
		        loadingIndicator.bringToFront();
		        
				mMediaPlayer = new MediaPlayer();
				mSurface.getHolder().addCallback(new Callback() {
					@Override
					public void surfaceDestroyed(SurfaceHolder arg0) {
					}
					
					@Override
					public void surfaceCreated(SurfaceHolder holder) {
						mMediaPlayer.setDisplay(holder);
					}
					
					@Override
					public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
					}
				});
				
				mMediaPlayer.setOnInfoListener(new OnInfoListener() {
	                @Override
	                public boolean onInfo(MediaPlayer mp, int what, int extra) {
	                    if (what == MediaPlayer.MEDIA_INFO_BUFFERING_START) {
	                        loadingIndicator.setVisibility(View.VISIBLE);
	                    } else if (what == MediaPlayer.MEDIA_INFO_BUFFERING_END) {
	                    	loadingIndicator.setVisibility(View.GONE);
	                    }
	                    return false;
	                }
	            });
				
				mMediaPlayer.setOnVideoSizeChangedListener(new OnVideoSizeChangedListener() {

					/**
					 * Handling onVideoSizeChanged called by the MediaPlayer after initiating
					 * playback, scales video according to aspect ratio and display dimensions.
					 */
					@SuppressWarnings("deprecation")
					@Override
					public void onVideoSizeChanged(MediaPlayer mp, int width, int height) {
						RelativeLayout.LayoutParams vLayout = (RelativeLayout.LayoutParams) mSurface
								.getLayoutParams();
						
						WindowManager wm = (WindowManager) cordova.getActivity().getSystemService(Context.WINDOW_SERVICE);
						
						if( Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2 ) {
			                Point size = new Point();
			                wm.getDefaultDisplay().getSize(size);

							vLayout.width = size.x;
							vLayout.height = size.y;
						} else {
							vLayout.width = wm.getDefaultDisplay().getWidth();
							vLayout.height = wm.getDefaultDisplay().getHeight();
						}

						float aspectRatio = (float) width / height;
						float screenRatio = (float) vLayout.width / vLayout.height;
						float topMargin = 0, leftMargin = 0;

						if (screenRatio < aspectRatio)
							topMargin = (float) vLayout.height
									- ((float) vLayout.width / aspectRatio);
						else if (screenRatio > aspectRatio)
							leftMargin = (float) vLayout.width - (vLayout.height * aspectRatio);

						vLayout.setMargins((int) leftMargin, (int) topMargin, 0, 0);
						mSurface.setLayoutParams(vLayout);
					}
				});
				
				mMediaPlayer.setOnErrorListener(new OnErrorListener() {
					@Override
					public boolean onError(MediaPlayer mp, int what, int extra) {
						problemListener.gotProblem(OctoStatic.generateMediaPlayerProblem(what, extra));
						return true;
					}
				});
				
				mMediaPlayer.setOnCompletionListener(new OnCompletionListener() {
					@Override
					public void onCompletion(MediaPlayer mp) {
						if (!urlQueue.isEmpty()) {
							playStream(urlQueue.removeFirst());
						} else {
							if( dialog != null ) {
								dialog.dismiss();
								Toast t = new Toast(cordova.getActivity());
								t.setText("Streaming ended.");
								t.show();
							}
						}
					}
				});

	            WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
	            lp.copyFrom(dialog.getWindow().getAttributes());
	            lp.width = WindowManager.LayoutParams.MATCH_PARENT;
	            lp.height = WindowManager.LayoutParams.MATCH_PARENT;
	            
	            dialog.setContentView(main);
	            dialog.show();
	            dialog.getWindow().setAttributes(lp);
            }
        };
        this.cordova.getActivity().runOnUiThread(runnable);
	}
	
	/**
	 * Setting up and playing a received media URL  
	 * 
	 * @param mediaUrl URL which needs to be passed to a media player
	 * @param playerId the id of the media player which should be used to play
	 * 			the media Url 
	 */
	protected void playStream(final Uri mediaUrl) {
		Log.d(LOG_TAG,  "Now playing: " + mediaUrl);
		
        // Create dialog in new thread
        Runnable runnable = new Runnable() {
            public void run() {
				try {
					mMediaPlayer.stop();
					mMediaPlayer.setDataSource(cordova.getActivity(), mediaUrl);

					mMediaPlayer.prepare();
					mMediaPlayer.start();
				} catch (Exception e) {
					Log.e(LOG_TAG, "Error preparing MediaPlayer", e);
					try {
						JSONObject obj = new JSONObject();
						obj.put("type", ERROR_EVENT);
						obj.put("message", e.getMessage());
						sendUpdate(obj, true, PluginResult.Status.ERROR);
			        } catch (JSONException ex) {
			        	Log.d(LOG_TAG, "Should never happen");
					}
					if( dialog != null ) {
						dialog.dismiss();
					}
				}
            }
        };
        this.cordova.getActivity().runOnUiThread(runnable);
	}

	/**
	 * Adding a stream to the OctoMediaPlayer. Creates an StreamPlayer the
	 * StreamPlayer instance is initiated with it's own UrlListener and
	 * ProblemListener.
	 * 
	 * @param stream
	 *            link (e.g., octoshape://ond.octoshape.com/demo/ios/bbb.mp4)
	 * @return StreamPlayer on which we can request playback.
	 */
	public StreamPlayer setupStream(final String stream) {
		Log.d(LOG_TAG, "Setting up stream: " + stream);
		StreamPlayer sp = os.createStreamPlayer(stream);
		sp.setProblemListener(problemListener);
		sp.setListener(new StreamPlayerListener() {
			/**
			 * Receiving new URL from the streamplayer object either due to
			 * requesting playback, seeking or experiencing a bitrate/resolution
			 * changes requiring the re-initialization of the Player.
			 * 
			 * @param url
			 *            to be passed to the media player
			 * @param seekOffset
			 *            offset we have seek to in milliseconds
			 * @param playAfterBuffer
			 *            if true the URL should be added to a list and played
			 *            upon completion of the current URL.
			 */
			@Override
			public void gotUrl(String url, long seekOffset,
					boolean playAfterBuffer) {
				if (playAfterBuffer && mMediaPlayer.isPlaying()) {
					urlQueue.add(Uri.parse(url));
				} else {
					urlQueue.clear();
					playStream(Uri.parse(url));
				}
			}

			@Override
			public void resolvedNativeSeek(boolean isLive, String playerId) {
			}
			@Override
			public void resolvedOsaSeek(boolean isLive, long duration, String playerId) {
			}
			@Override
			public void resolvedNoSeek(boolean isLive, String playerId) {
			}
			@Override
			public void gotNewOnDemandStreamDuration(long duration) {
			}
		});
		return sp;
	}

	public void closePlayer() {
		if(mMediaPlayer != null){
			mMediaPlayer.release();
		}
		if(mStreamPlayer != null){
			mStreamPlayer.close(null);
		}
	}
	
	ProblemListener problemListener = new ProblemListener() {
		@Override
		public void gotProblem(final Problem p) {
			Log.e(LOG_TAG, "Problem: "+p.toString());
			try {
				JSONObject obj = new JSONObject();
				obj.put("type", ERROR_EVENT);
				obj.put("code", p.getErrorCode());
				obj.put("message", p.getMessage());
				sendUpdate(obj, true, PluginResult.Status.ERROR);
	        } catch (JSONException ex) {
	        	Log.d(LOG_TAG, "Should never happen");
			}/*
			if( dialog != null ) {
				dialog.dismiss();
			}*/
		}
	};
	
    /**
     * Create a new plugin success result and send it back to JavaScript
     *
     * @param obj a JSONObject contain event payload information
     */
    private void sendUpdate(JSONObject obj, boolean keepCallback) {
        sendUpdate(obj, keepCallback, PluginResult.Status.OK);
    }

    /**
     * Create a new plugin result and send it back to JavaScript
     *
     * @param obj a JSONObject contain event payload information
     * @param status the status code to return to the JavaScript environment
     */
    private void sendUpdate(JSONObject obj, boolean keepCallback, PluginResult.Status status) {
		PluginResult result = new PluginResult(status, obj);
		result.setKeepCallback(keepCallback);
		this.callbackContext.sendPluginResult(result);
    }

}
