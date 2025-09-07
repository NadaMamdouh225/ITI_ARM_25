<?php
if(isset($_GET['LedState']))
{
    $Fobj = fopen("state.txt",'w');
    if($_GET['LedState'] == 'on')
    {
        fwrite($Fobj,'1');
    }elseif($_GET['LedState']=='off')
    {
        fwrite($Fobj,'0'); 
    }
    fclose($Fobj);
}


?>