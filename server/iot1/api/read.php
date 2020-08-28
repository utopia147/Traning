<?php
header("Content-Type: application/json; charset=UTF-8");
require '../connect.php';


$sql = 'SELECT `relayid`, `status` FROM `relay`';

$result = mysqli_query($con, $sql);

while ($row = mysqli_fetch_assoc($result)) {
    $array[] = $row;
}
$json = json_encode($array, JSON_PRETTY_PRINT);
echo $json;
