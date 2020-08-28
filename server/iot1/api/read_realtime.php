<?php

require '../connect.php';


$sql = 'SELECT * FROM `dht`';

$result = mysqli_query($con, $sql);


$output .= '<table class="table table-dark">
    <thead>
      <tr>
        <th scope="col">DHT</th>
        <th scope="col">Temp</th>
        <th scope="col">Humidity</th>
        <th scope="col">Status</th>
        <th scope="col">Time</th>
      </tr>
    </thead>
    <tbody>';
while ($row = mysqli_fetch_assoc($result)) {
    $output .= '
      <tr>
        <th scope="row">' . $row['id'] . '</th>
        <td><h2 class="btn btn-dark">' . $row['temp'] . ' *C <i class="fas fa-thermometer-three-quarters"></i></h2></td>
        <td><h2 class="btn btn-light">' . $row['humidity'] . ' % <i class="fas fa-tint"></i></h2></td>';
    if ($row['temp'] > 40) {
        $output .= '<td><h2 class="btn btn-danger"> Too Hot! <i class="fab fa-hotjar"></i></h2></td>';
    } elseif ($row['temp'] > 20) {
        $output .= '<td><h2 class="btn btn-success"> Nice! <i class="fas fa-smile-wink"></i></h2></td>';
    } elseif ($row['temp'] < 20) {
        $output .= '<td><h2 class="btn btn-primary"> So cool! <i class="fas fa-snowflake"></i> </h2></td>';
    }

    $output .= '
        <td>' . $row['timestamp'] . ' <i class="far fa-clock"></i></td>
      </tr>
      ';
}
$output .= '
    </tbody>
  </table>';

echo $output;

mysqli_close($con);
