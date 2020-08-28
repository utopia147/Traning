<?php
  $host = 'localhost';
  $user = 'root';
  $pass = '12345678';
  $db = 'iot1';
  $con = mysqli_connect($host , $user , $pass, $db);
  mysqli_set_charset($con ,'utf8');
