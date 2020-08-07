import 'dart:async';
// ignore: unused_import
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:liquid_pull_to_refresh/liquid_pull_to_refresh.dart';

class WeatherPrediction extends StatefulWidget {
  @override
  _WeatherPredictionState createState() => _WeatherPredictionState();
}

class _WeatherPredictionState extends State<WeatherPrediction> {
  final url = 'https://thingspeak.com/channels/1098741/feed.json';
  var items;
  var temperature;
  var humidity;
  var dewPoints;
  var absolutePressure;
  var relativePressure;
  int rain;
  String rainStatus;

  // ignore: missing_return
  Future<String> getResponse() async {
    final response =
        await http.get(url, headers: {'Accept': 'application/json'});
    Map map = json.decode(response.body) as Map;
    setState(() {
      items = map['feeds'];
      temperature = items[99]['field1'];
      humidity = items[99]['field2'];
      dewPoints = items[99]['field3'];
      absolutePressure = items[99]['field4'];
      relativePressure = items[99]['field5'];
      rain = int.parse(items[99]['field7']);
    });
  }

  Widget textWidget({String text, double textSize}) {
    return Center(
      child: Text(
        "$text",
        style: TextStyle(fontSize: textSize, color: Colors.black),
        textAlign: TextAlign.center,
      ),
    );
  }

  @override
  void initState() {
    super.initState();
    getResponse();
  }

  @override
  Widget build(BuildContext context) {
    var boxSide = MediaQuery.of(context).size.width * 0.10;
    return Scaffold(
      appBar: AppBar(
        title: Text(
          'Weather Prediction',
          style: TextStyle(fontSize: boxSide * 0.50),
        ),
        centerTitle: true,
      ),
      body: LiquidPullToRefresh(
        springAnimationDurationInMilliseconds: 100,
        showChildOpacityTransition: false,
        onRefresh: getResponse,
        child: items == null
            ? Center(
                child: Text(
                  'Fetching Data Please Wait....',
                  style: TextStyle(fontSize: boxSide * 0.70),
                  textAlign: TextAlign.center,
                ),
              )
            : Container(
                decoration: BoxDecoration(
                    gradient: LinearGradient(
                        colors: [Colors.blue, Colors.white],
                        begin: Alignment.topCenter)),
                child: ListView(
                  children: [
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text: 'Temperature: $temperature °C',
                        textSize: boxSide * 0.70),
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text: 'Humidity: $humidity %',
                        textSize: boxSide * 0.70),
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text: 'Dew Points: $dewPoints •c',
                        textSize: boxSide * 0.70),
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text: 'Absolute Pressure: $absolutePressure hpa',
                        textSize: boxSide * 0.70),
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text: 'Relative Pressure: $relativePressure hpa',
                        textSize: boxSide * 0.70),
                    SizedBox(
                      height: boxSide,
                      width: boxSide,
                    ),
                    textWidget(
                        text:
                            'Rain: ${rain <= 300 ? 'Heavy Rain' : rain >= 400 && rain <= 800 ? 'Normal Rain' : 'Dry'}',
                        textSize: boxSide * 0.80),
                  ],
                ),
              ),
      ),
    );
  }
}
