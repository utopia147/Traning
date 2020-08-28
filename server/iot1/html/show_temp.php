<?php
require '../connect.php';
$sql = 'SELECT * FROM `dht`';
$result = mysqli_query($con, $sql);
?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Temp</title>
</head>

<body>
    <table border="10">
        <tr>
            <th>
                NO
            </th>
            <th>
                Temp
            </th>
            <th>
                Humandity
            </th>
            <th>
                Timestamp
            </th>
        </tr>
        <?php

        while ($row = mysqli_fetch_assoc($result)) {
            $no++ ?>
            <tr>
                <td>
                    <?php echo $no; ?>
                </td>
                <td>
                    <?php echo $row['temp']; ?>
                </td>
                <td>
                    <?php echo $row['humidity']; ?>
                </td>
                <td>
                    <?php echo $row['timestamp']; ?>
                </td>
            </tr>
        <?php
        }
        mysqli_close($con);
        ?>
    </table>
</body>

</html>