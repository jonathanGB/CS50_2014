<?php

    // configuration
    require("../includes/config.php"); 
    
    $user = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION['id']);
    $user = $user[0]; // only the first line
    $portfolio_rows = query("SELECT symbol, amount FROM shares WHERE user_id = ?", $_SESSION['id']);
    
    $positions = [];
    foreach ($portfolio_rows as $portfolio_row)
    {
        $stock = lookup($portfolio_row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $portfolio_row["amount"],
                "symbol" => strtoupper($portfolio_row["symbol"]),
                "value" => ($portfolio_row["amount"] * $stock["price"])
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "user" => $user, "title" => "Portfolio"]);

?>
