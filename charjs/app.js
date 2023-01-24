const express=require('express')
const cors=require('cors')

const app=express() 
const port= 3000 


const mysql=require('mysql') 
app.use(express());
app.use(cors());

var con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "iot"
  });





  app.get('/getHumid',(req,res) => {
    con.query("SELECT hum FROM iot ORDER BY ID DESC LIMIT 1", function (err, result, fields) {
     
      if (err) throw err;
     
      Object.keys(result).forEach(function(key) {
        var row = result[key];
     
      res.status(200).send(""+row.hum)
        
      });
    });
  });
    
    

  app.get('/getTemp',(req,res) => {
    con.query("SELECT temp FROM iot ORDER BY ID DESC LIMIT 1", function (err, result, fields) {
     
      if (err) throw err;
     
      Object.keys(result).forEach(function(key) {
        var row = result[key];
    
      res.status(200).send(""+row.temp)
        
      });
    });
  });

  app.get('/getx',(req,res) => {
    con.query("SELECT x FROM iot ORDER BY ID DESC LIMIT 1", function (err, result, fields) {
     
      if (err) throw err;
     
      Object.keys(result).forEach(function(key) {
        var row = result[key];
    
      res.status(200).send(""+row.x)
        
      });
    });
  });

  app.get('/getz',(req,res) => {
    con.query("SELECT z FROM iot ORDER BY ID DESC LIMIT 1", function (err, result, fields) {
     
      if (err) throw err;
     
      Object.keys(result).forEach(function(key) {
        var row = result[key];
        console.log(row.z)
      res.status(200).send(""+row.z)
        
      });
    });
  });

    app.get('/gety',(req,res) => {
    con.query("SELECT y FROM iot ORDER BY ID DESC LIMIT 1", function (err, result, fields) {
     
      if (err) throw err;
     
      Object.keys(result).forEach(function(key) {
        var row = result[key];
        console.log(row.y)
      res.status(200).send(""+row.y)
        
      });
    });
  });


app.listen(port,()=>{console.log('Notre application sur le port {port}') 
})