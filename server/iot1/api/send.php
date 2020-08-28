<?php

require '../connect.php';

header('Content-type: aplication/json');
$json = file_get_contents("php://input");
$data = json_decode($json, true);

$id = $data['id'];
$temp = $data['temp'];
$humidity = $data['humidity'];

if ($id || $temp || $humidity != NULL) {
    $sqlUpdateTemp = "UPDATE `dht` SET `temp`= $temp ,`humidity`= $humidity , `timestamp` = CURRENT_TIMESTAMP WHERE id = $id ";
    $result = mysqli_query($con, $sqlUpdateTemp);

    if ($result) {
        echo "Done query";
    }
} else {
    echo "Please send id:val , temp:val , humidity:,val";
}
