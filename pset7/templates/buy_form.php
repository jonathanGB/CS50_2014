<h2> Portfolio of <?= $user['username'] ?> </h2>

<form method="post" action="buy.php">
    <table class="table table-bordered table-striped">
        <thead>
            <tr>
                <th> Stock </th>
                <th> Shares </th>
                <th> To buy </th>
                <th> Price </th>
                <th> Value </th>
            </tr>
        </thead>
        <tfoot>
            <tr>
                <th><em>Buy another stock</em></th>
                <th><label for="buy_symbol">Stock's symbol </label> <input type="text" id="buy_symbol" name="buy_symbol"></th>
                <th><label for="buy_amount">Amount </label> <input type="number" id="buy_amount" name="buy_amount" min="0" max="<?= $max_per_buy ?>">
            </tr>
        </tfoot>
        <tbody>
            <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= '<a href="http://finance.yahoo.com/q?s='.$position["symbol"].'" target="_blank">'?><?= $position['name']?></a> (<?= strtoupper($position["symbol"]) ?>)</td>
                <td><?= $position["shares"] ?></td>
                <td><?= '<input type="number" name="'.$position["symbol"].'" min="0" max="'.$position["max_per_stock"].'">'?></td>
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
