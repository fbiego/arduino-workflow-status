<?php

function sendStatus($bot_token, $chat_id, $status)
{
    $cURLConnection = curl_init();
    curl_setopt(
        $cURLConnection,
        CURLOPT_URL,
        "https://api.telegram.org/bot" . $bot_token . "/sendMessage?chat_id=" .$chat_id . "&parse_mode=html&text=" . urlencode($status)
    );
    curl_setopt($cURLConnection, CURLOPT_RETURNTRANSFER, true);
    $json = curl_exec($cURLConnection);
    curl_close($cURLConnection);
	
}


sendStatus($argv[1], $argv[2], $argv[3]);


?>
