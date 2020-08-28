<?php
require '../connect.php';
$sql = "SELECT * FROM `relay`";
$result = mysqli_query($con, $sql);

if ($_POST['submit'] != null) {

    foreach ($_POST as $key => $value) {
        if ($key != 'submit') {
            // echo "$key : $value ";
            $sqlupdate = "UPDATE `relay` SET `status`=$value WHERE relayid = $key ";
            $resultUpdate = mysqli_query($con, $sqlupdate);
        }
    }
    if ($resultUpdate) {
        echo ' <script type="text/javascript">
        window.location="./control_relay.php";
        </script>';
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control Relay</title>
</head>

<body>
    <form class="form1" method="post" action="" enctype="multipart/form-data">
        <?php
        while ($row = mysqli_fetch_array($result)) {
            $no++

        ?>
        <h1>
            <?php echo 'Relay ' . $no ?></h1>

        <h2><?php echo $row['name'] ?>
        </h2>
        <select class="form-control" name="<?php echo $row['relayid'] ?>">
            <?php

                ?>
            <option value="1" <?php if ($row['status'] == 1) {
                                        echo 'selected="selected"';
                                    } ?>>ON
            </option>
            <option value="0" <?php if ($row['status'] == 0) {
                                        echo 'selected="selected"';
                                    } ?>>OFF
            </option>
        </select>

        <h1>Status : <?php if ($row['status'] == 1) {
                                echo 'ON';
                            } else {
                                echo 'OFF';
                            } ?></h1>

        <?php
        }
        ?>
        <button type="submit" name='submit' value='submit'>ยืนยัน</button>
    </form>

</html>