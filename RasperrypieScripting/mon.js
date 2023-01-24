const express=require('express')
const app=express()
const port= 3000

const mysql=require('mysql')
const byline = require('byline');
const fs = require('fs');
const nthline = require("nthline");
let filePath = "mqtt.txt";


var body = require ('body-parser');
var myPythonScript = "/home/pi/myapp/mqtt.py";
//var myPythonScript = "/home/pi/mqtt.py";

var pythonExecutable = "python";


var uint8arrayToString = function(data) {
    return String.fromCharCode.apply(null, data);
};


const spawn = require('child_process').spawn;
// The '-u' tells Python to flush every time
const scriptExecution = spawn(pythonExecutable, ['-u', myPythonScript]);
scriptExecution.stdout.on('data',(data) => {
    var a=uint8arrayToString(data);
    console.log(a);
 
  const connection = mysql.createConnection({
  host: "172.20.10.4",
  user: "usera",
  password: "passa",
  database: "iot",
});

connection.connect();
connection.query("SELECT 1 + 1 AS solution", (err, rows, fields) => {
  if (err) throw err;

  console.log("connected to db");
});
const nthline = require("nthline");
let filePath = "mqtt.txt";
let rowIndex = [1, 2, 3, 4, 5];
const saveToDB = async () => {
  let hum = await nthline(rowIndex[0], filePath);
  let temp = await nthline(rowIndex[1], filePath);
  let x = await nthline(rowIndex[2], filePath);
  let y = await nthline(rowIndex[3], filePath);
  let z = await nthline(rowIndex[4], filePath);
  connection.query(
    `INSERT INTO iot (hum,temp,x,y,z) VALUES ("${hum}","${temp}","${x}","${y}","${z}")`
  );
  //console.log(hum + temp + x + y + z);
};
setInterval(function () {
  let newArray = rowIndex.map((i) => i + 5);
  rowIndex = newArray;
  saveToDB();
}, 10000);    
});
