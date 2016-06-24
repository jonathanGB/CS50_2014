<h2> History of <?= $user['username'] ?> </h2>

<table class="table table-bordered table-striped">
    <thead>
        <tr>
            <th> Date </th>
            <th> Transaction type </th>
            <th> Stock </th>
            <th> Shares </th>
            <th> Price </th>
            <th> Cash variation </th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>

        <tr>
            <td> <?= $position['time'] ?> </td>
            <td> <?= $position['transaction'] ?> </td>
            <td><?= '<a href="http://finance.yahoo.com/q?s='.$position["symbol"].'" target="_blank">'?><?= $position['name']?></a> (<?= $position["symbol"] ?>)</td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?> $</td>
            <td style="color: <?= $position['colour'] ?>"><?= $position["cash_variation"] ?> $</td>
        </tr>

        <?php endforeach ?>
    </tbody>
</table>
<br>
<div>
    <a href="logout.php">Log Out</a>
</div>
