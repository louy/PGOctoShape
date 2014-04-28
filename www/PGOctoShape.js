var exec = require('cordova/exec');
var channel = require('cordova/channel');
var modulemapper = require('cordova/modulemapper');

function PGOctoShape() {
   this.channels = {
        'start' : channel.create('start'),
        'stop'  : channel.create('stop'),
        'error' : channel.create('error'),
   };
}

PGOctoShape.prototype = {
    init: function() {
        var self = this;
        var cb = function(eventname) {
           self._eventHandler(eventname);
        };
        exec(cb, cb, "PGOctoShape", "init", []);
    },

    _eventHandler: function (event) {
        if (event.type in this.channels) {
            this.channels[event.type].fire(event);
        }
    },

    play: function(OctoLink, success, fail) {
        exec(success, fail, "PGOctoShape", "play", [OctoLink]);
        return this;
    },

    stop: function (success, fail) {
        exec(success, fail, "PGOctoShape", "stop", []);
    },

    addEventListener: function (eventname,f) {
        if (eventname in this.channels) {
            this.channels[eventname].subscribe(f);
        }
    },
    removeEventListener: function(eventname, f) {
        if (eventname in this.channels) {
            this.channels[eventname].unsubscribe(f);
        }
    },
};

module.exports = new PGOctoShape();

//document.addEventListener('deviceready', module.exports.init, false);
