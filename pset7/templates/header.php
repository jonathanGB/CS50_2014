<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <header id="top">
                <a href="index.php"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
                
                <?php if (isset($_SESSION['id'])) : ?>
                    <ul class="nav nav-pills center">
                      <li><a href="index.php">Portfolio</a></li>
                      <li><a href="quote.php">Look up</a></li>
                      <li><a href="buy.php">Buy</a></li>
                      <li><a href="sell.php">Sell</a></li>
                      <li><a href="history.php">History</a></li>
                    </ul>
                <?php endif ?>
            </header>

            <div id="middle">
