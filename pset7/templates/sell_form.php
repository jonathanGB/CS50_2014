<h2> Portfolio of <?= $user['username'] ?> </h2>

<form method="post" action="sell.php">
    <table class="table table-bordered table-striped">
        <thead>
            <tr>
                <th> Stock </th>
                <th> Shares </th>
                <th> To sell </th>
                <th> Price </th>
                <th> Value </th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($positions as $position): ?>

            <tr>
                <td><?= '<a href="http://finance.yahoo.com/q?s='.$position["symbol"].'" target="_blank">'?><?= $position['name']?></a> (<?= strtoupper($position["symbol"]) ?>)</td>
                <td><?= $position["shares"] ?></td>
                <td><?= '<input type="number" name="'.$position["symbol"].'" min="0" max="'.$position["shares"].'">'?></td>
                <td><?= $position["price"] ?> $</td>
                <td><?= $position["value"] ?> $</td>
            </tr>

            <?php endforeach ?>
        </tbody>
    </table>
    <input type="submit" class="btn btn-default" value="Submit" />
</form>
<br>
<div>
    <h4> Cash balance: <?= $user["cash"] ?></h4> <br>
    <a href="logout.php">Log Out</a>
</div>
