<?

/*
 *  This program will convert GIF files into MAP and TER files, the kind
 *  that the mud reads. You will need PHP and the GD image library to use
 *  this script.
 *
 */

include('inc.inc');

$write_dir = '/';


if(!$_GET) {


?>
<html>
<head>
	<link rel="stylesheet" href="css.css" type="text/css">
</head>
<body>

<p>
Below are the GIF files in the current directory. The program will convert the image to a mud
map file and remove the trailing <b>.gif</b> of the filename. Files with <b>.ter</b> in the name
will be rendered as terrain files, all others will be rendered as map files.
</p>

<?


echo '<p><b>Write Dir:</b> ' . $write_dir . '</p>';


	if($open = @opendir('.')) {

		echo '<ul>';

		while(false !== ($file = readdir($open))) {

			if($file != '.' && $file != '..') {

				//echo '<li>';

				if($file != clean($file)) {

					echo '<li class="invalid">' . hsc($file) . ' - cannot open, file contains invalid characters.</li>';

				} else if(substr($file, -4) == '.gif') {

					echo '<li><a href="?file=' . $file . '">' . $file . '</a>, layer: <span class="green">' . (isTer($file) ? 'terrain' : 'map') . '</span>.</li>';

				} else {

					////echo '<span class="noopen">' . $file . ' - cannot open, not a GIF file.</span>';

				}

				//echo '</li>';

			}

		}

		echo '</ul>';

	}

	echo '</body></html>';
	exit;

}



$file = $_GET['file'];



if(substr($file, -4) != '.gif' || $file != clean($file)) {
	echo 'Invalid filename.';
	exit;
}

$what = getimagesize($file);

switch($what['mime']) {
	case 'image/png':
		$src_id = imagecreatefrompng( $file );
		break;
	case 'image/jpeg':
		$src_id = imagecreatefromjpeg( $file );
		break;
	case 'image/gif':
		$old_id = imagecreatefromgif( $file );
		$src_id = imagecreatetruecolor( $what[0],$what[1]);
		imagecopy( $src_id, $old_id, 0, 0, 0, 0, $what[0], $what[1]);
		break;
	default: break;
}




function get_terrain($type, $r, $g, $b) {

	if($type == 'derlith' || $type == 'default') {

		    if($r==41  && $g==140 && $b==181)	return 'w';	// coastal water
		elseif($r==14  && $g==110 && $b==150)	return 'W';	// deep ocean water
		elseif($r==0   && $g==255 && $b==255)	return 'z';	// frozen river
		elseif($r==58  && $g==190 && $b==244)	return 'R';	// river
		elseif($r==96  && $g==163 && $b==190)	return 'l';	// lake
		elseif($r==50  && $g==98  && $b==118)	return 'L';	// deep lake
		elseif($r==0   && $g==0   && $b==255)	return 'o';	// oasis

		elseif($r==231 && $g==214 && $b==148)	return 'h';	// hills
		elseif($r==82  && $g==33  && $b==41)	return 'm';	// mountain
		elseif($r==104 && $g==88  && $b==91)	return 'n';	// snowy mountain
		elseif($r==82  && $g==61  && $b==64)	return '^';	// mountain peak
		elseif($r==176 && $g==96  && $b==107)	return 'v';	// volcano

		elseif($r==114 && $g==101 && $b==63)	return 's';	// swamp

		elseif($r==201 && $g==255 && $b==205)	return 'g';	// grassland

		elseif($r==255 && $g==255 && $b==171)	return 'd';	// desert
		elseif($r==161 && $g==142 && $b==69)	return 'i';	// sand dunes

		elseif($r==56  && $g==208 && $b==97)	return 'j';	// jungle
		elseif($r==0   && $g==169 && $b==46)	return 'J';	// dense jungle
		elseif($r==33  && $g==123 && $b==57)	return 'f';	// deciduous forest
		elseif($r==17  && $g==65  && $b==30)	return 'F';	// deep deciduous forest
		elseif($r==35  && $g==191 && $b==160)	return 'e';	// evergreen forest
		elseif($r==54  && $g==111 && $b==100)	return 'E';	// think evergreen forest

		elseif($r==242 && $g==255 && $b==212)	return 'p';	// plains

		elseif($r==255 && $g==255 && $b==255)	return 'r';	// glacier

	} elseif($type == 'underdark') {

		    if($r==82  && $g==33  && $b==41)	return 'm';	// mountain
		elseif($r==202 && $g==202 && $b==202)	return 'c';	// cavern floor

	}

	return '?';
}

function get_map($type, $r, $g, $b) {
	    if($r==136 && $g==136 && $b==136)	return '-';
	elseif($r==68  && $g==68  && $b==68)	return '|';
	elseif($r==170 && $g==170 && $b==170)	return '\\';
	elseif($r==221 && $g==221 && $b==221)	return '/';
	elseif($r==17  && $g==17  && $b==17)	return '+';

	elseif($r==255 && $g==0   && $b==0)	return 'C';
	elseif($r==170 && $g==0   && $b==0)	return 'V';
	elseif($r==106 && $g==0   && $b==0)	return 'T';

	elseif($r==106 && $g==0   && $b==129)	return '?';

	elseif($r==255 && $g==255 && $b==0)	return '>';

	// 0,0,0 marker
	elseif($r==128 && $g==128 && $b==128)	return '*';
	return ' ';
}




$data = '';



if($src_id) {

	$x_size = imagesx( $src_id );
	$y_size = imagesy( $src_id );

	$xj = 1;
	$yj = 1;

	$type = substr($file, 0, strpos($file, '.'));


	// char/strings that will construct the image. it's randomly selected after,
	// in the loop. a value in the array will be one pixel in the asci-image.


	// now it has a 'nested loop' to read 'each' pixel and print it
	for($y=0; $y<$y_size; $y+=$yj) {

		$line = '';

		for($x=0; $x<$x_size; $x+=$xj) {

			if($x>=$x_size || $y>=$y_size ) break;

			$rgb = @imagecolorat($src_id, $x, $y);
			$r = ($rgb >> 16) & 0xFF;
			$g = ($rgb >> 8) & 0xFF;
			$b = $rgb & 0xFF;


			if(isTer($file)) {

				$line .= get_terrain($type, $r, $g, $b);

			} else {

				$line .= get_map($type, $r, $g, $b);

			}


		}

		$data .= $line . "\n";

	}

	write($write_dir . substr($file, 0, -4), $data);

}



header('Location: pixel.php');



?>