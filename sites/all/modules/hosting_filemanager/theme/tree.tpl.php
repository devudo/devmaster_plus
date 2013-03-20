<?php
/**
 *
 */
?>

<ul class="jqueryFileTree" style="display:none;">

  <?php foreach ($tree as $name => $item) { ?>
    <li class="<?php print $item['class']; ?>"><?php print $item['data']?></li>
  <?php } ?>

</ul>
