var UK_URL = 'http://api.vateud.net/online/atc/eg,lon,essex,thames,solent.json';
var GW = 0;
var SS = 0;
var KK = 0;
var LL = 0;
var GD = 0;
var CC = 0;
var PH = 0;
var LON = "";

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function getOnline() {
  xhrRequest(UK_URL, "GET", function(response) {
    var data = JSON.parse(response);
    
    for (var i = 0; i < data.length; i++) {
      var call = data[i].callsign;
      var station = ((data[i].callsign).split("_"))[0];
      var loc = ((data[i].callsign).split("_"))[1];
      var pos = ((data[i].callsign).split("_"))[(((data[i].callsign).split("_")).length)-1];
      console.log(call);
      
      // stations available
      // GW SS KK LL GD CC PH
      if (station == "EGGW") {
        if (pos == "GND" && GW < 1) {
          GW = 1;
        } else if (pos == "TWR" && GW < 2) {
          console.log("TWR online!");
          GW = 2;
        } else if (pos == "APP" && GW < 3) {
          GW = 3;
        }
      } else if (station == "EGSS") {
        if (pos == "GND" && SS < 1) {
          SS = 1;
        } else if (pos == "TWR" && SS < 2) {
          SS = 2;
        } else if (pos == "APP" && SS < 3) {
          SS = 3;
        }
      } else if (station == "EGKK") {
        if (pos == "GND" && KK < 1) {
          KK = 1;
        } else if (pos == "TWR" && KK < 2) {
          KK = 2;
        } else if (pos == "APP" && KK < 3) {
          KK = 3;
        }
      } else if (station == "EGLL") {
        if (pos == "GND" && LL < 1) {
          LL = 1;
        } else if (pos == "TWR" && LL < 2) {
          LL = 2;
        } else if (pos == "APP" && LL < 3) {
          LL = 3;
        }
      } else if (station == "EGGD") {
        if (pos == "GND" && GD < 1) {
          GD = 1;
        } else if (pos == "TWR" && GD < 2) {
          GD = 2;
        } else if (pos == "APP" && GD < 3) {
          GD = 3;
        }
      } else if (station == "EGCC") {
        if (pos == "GND" && CC < 1) {
          CC = 1;
        } else if (pos == "TWR" && CC < 2) {
          CC = 2;
        } else if (pos == "APP" && CC < 3) {
          CC = 3;
        }
      } else if (station == "EGPH") {
        if (pos == "GND" && PH < 1) {
          PH = 1;
        } else if (pos == "TWR" && PH < 2) {
          PH = 2;
        } else if (pos == "APP" && PH < 3) {
          PH = 3;
        }
      } else if (station == "ESSEX") {
        GW = 3;
        SS = 3;
      } else if (station == "LON" && station != "LON_CTR") {
        LON.concat(loc + ", ");
      } else if (call == "LON_CTR") {
        LON.concat("BB,");
      }
    }
    console.log(LON);
    var dict = {
      "KEY_GW": GW,
      "KEY_SS": SS,
      "KEY_KK": KK,
      "KEY_LL": LL,
      "KEY_GD": GD,
      "KEY_CC": CC,
      "KEY_PH": PH,
      "KEY_LON": LON
    };
    
    Pebble.sendAppMessage(dict, function(e) {
      console.log("Success sending to Pebble");
    }, function(e) {
      console.log("Error sending to Pebble");
    });
    
  });
}

Pebble.addEventListener("ready", function() {
  console.log("PebbleKit JS ready!");
  getOnline();
});

Pebble.addEventListener("appmessage", function() {
  getOnline();
});