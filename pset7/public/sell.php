<?php
    // configuration
    require("../includes/config.php");
    
    $user = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION['id']);
    $user = $user[0];
    $portfolio_rows = query("SELECT symbol, amount FROM shares WHERE user_id = ?", $_SESSION['id']);
    $change = 0;
    $positions = [];
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        foreach($portfolio_rows as $portfolio_row)
        {
            $symbol = $portfolio_row['symbol'];
            $stock = lookup($portfolio_row["symbol"]);
            
            if ($stock !== false)
            {   
                if (!empty($_POST[$symbol]))
                {
                    $change++;
                    $shares = $portfolio_row["amount"] - $_POST[$symbol];
                    $revenue = $stock['price'] * $_POST[$symbol];
                    
                    $update_user = query("UPDATE users SET cash = (cash + ?) WHERE id = ?", $revenue, $_SESSION['id']);
                    $update_history = query("INSERT INTO `history`(`user_id`, `transaction`, `name`, `symbol`, `amount`, `price`, `time`) VALUES (?,?,?,?,?,?, NOW())",
                                           $_SESSION['id'], 'Sell', $stock['name'], $symbol, $_POST[$symbol], $stock['price']);
                    
                    if ($shares == 0)
                        $delete_shares = query("DELETE FROM shares WHERE user_id = ? AND symbol = ?", $_SESSION['id'], $symbol);
                    else
                        $update_shares = query("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", $shares, $_SESSION['id'], $symbol);
                }
            }
        }
        $portfolio_updated_rows = query("SELECT symbol, amount FROM shares WHERE user_id = ?", $_SESSION['id']);
        $user = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION['id']);
        $user = $user[0];

        
        foreach($portfolio_updated_rows as $portfolio_updated_row)
        {
            $stock = lookup($portfolio_updated_row['symbol']);
            if ($stock !== false)
            {
                $positions[] = [
                        "name" => $stock["name"],
                        "price" => $stock["price"],
                        "shares" => $portfolio_updated_row["amount"],
                        "symbol" => $portfolio_updated_row["symbol"],
                        "value" => ($portfolio_updated_row["amount"] * $stock["price"])
                    ];
            }
        }
        render("sell.php", ["title" => "Portfolio", "user" => $user, "positions" => $positions]);
        
    }
    else
    {
        foreach ($portfolio_rows as $portfolio_row)
        {
            $stock = lookup($portfolio_row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $portfolio_row["amount"],
                    "symbol" => $portfolio_row["symbol"],
                    "value" => ($portfolio_row["amount"] * $stock["price"])
                ];
            }
        }

        // render portfolio
        render("sell_form.php", ["positions" => $positions, "user" => $user, "title" => "Sell"]);
    }
?>
