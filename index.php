<?php
	if (isset($_POST['sLine']) && trim($_POST['sLine']) != ""){
		$ip   = $_SERVER['REMOTE_ADDR'];
		file_put_contents('ip.txt', $ip."\n".date("H:i:s"));
		echo "1";
	}
	else
		echo "0\n";
?>