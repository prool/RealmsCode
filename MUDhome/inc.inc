<?

if(!function_exists('imagecreatefromgif')) {

echo '<html>
<head>
	<link rel="stylesheet" href="css.css" type="text/css">
</head>
<body>

<h1>Map Editor</h1>

<p>It looks like the GD image library is not installed; this script will not work.</p>

</body>
</html>
';
exit;

}


function clean($text) {
	return(preg_replace('/[^-.a-zA-Z0-9_]/', '', $text));
}
function hsc($text) {
	return htmlspecialchars($text, ENT_QUOTES);
}

function isTer($text) {
	return(strstr($text, '.ter'));
}


/*
 *	void write(string $file, string $text)
 *
 *	Writes the supplied text to a file.
 */

function write($file, $text) {

	$handle = @fopen($file, 'wb');
	@flock($handle, LOCK_EX);
	@fwrite($handle, $text);
	@fclose($handle);

}

?>