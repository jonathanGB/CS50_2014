<?php
    // configuration
    require("../includes/config.php");
    
    $user = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION['id']);
    $user = $user[0];
    $portfolio_rows = query("SELECT symbol, amount FROM shares WHERE user_id = ?", $_SESSION['id']);
    $change = 0;
    $cost = 0;
    $positions = [];
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $buy_symbol = strtoupper(htmlspecialchars($_POST['buy_symbol']));
        $buy_amount = htmlspecialchars($_POST['buy_amount']);
        
        // valid transaction?      
        if (!empty($buy_symbol) && !empty($buy_amount))
        {
            $stock = lookup($buy_symbol);
            
            if ($stock !== false)
            {
                $cost = $buy_amount * $stock['price'];
            }
            else
                apologize("This symbol is not valid.");
        }
        foreach($portfolio_rows as $portfolio_row)
        {
            $symbol = $portfolio_row['symbol'];
            $stock = lookup($portfolio_row["symbol"]);
            
            if ($stock !== false)
            {   
                if (!empty($_POST[$symbol]))
                {
                    $cost += ($stock['price'] * $_POST[$symbol]);
                }
            }
        }
        
        if ($cost > $user['cash'])
            apologize("You don't have the funds necessary for this transaction.");
        else
            $update = query("UPDATE users SET cash = (cash - ?) WHERE id = ?", $cost, $_SESSION['id']);

        // look through the modifications of the portfolio
        foreach($portfolio_rows as $portfolio_row)
        {
            $symbol = $portfolio_row['symbol'];
            $stock = lookup($portfolio_row["symbol"]);
            
            if ($stock !== false)
            {   
                if (!empty($_POST[$symbol]))
                {
                    $change++;
                    $shares = $portfolio_row["amount"] + $_POST[$symbol];
                    
                    $update_shares = query("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", $shares, $_SESSION['id'], $symbol);
                    $update_history = query("INSERT INTO `history`(`user_id`, `transaction`, `name`, `symbol`, `amount`, `price`, `time`) VALUES (?,?,?,?,?,?, NOW())",
                                           $_SESSION['id'], 'Buy', $stock['name'], $symbol, $_POST[$symbol], $stock['price']);
                }
            }
        }
        
        // if user buys another stock, make sure it isn't already in the table            
        if (!empty($buy_symbol) && !empty($buy_amount))
        {
            $stock = lookup($buy_symbol);
            
            $valid_insertion = query("INSERT INTO shares (user_id, symbol, amount) VALUES (?,?,?)", $_SESSION['id'], $buy_symbol, $buy_amount);
            
            if($valid_insertion === false)
                apologize("The stock you want to add is already in your portfolio.");
            
            $update_history = query("INSERT INTO `history`(`user_id`, `transaction`, `name`, `symbol`, `amount`, `price`, `time`) VALUES (?,?,?,?,?,?, NOW())",
                                           $_SESSION['id'], 'Buy', $stock['name'], $buy_symbol, $buy_amount, $stock['price']);
            $change++;
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
        render("buy.php", ["title" => "Portfolio", "user" => $user, "positions" => $positions]);
        
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
                    "value" => $portfolio_row["amount"] * $stock["price"],
                    "max_per_stock" => (int) ($user['cash'] / $stock['price']),
                ];
            }
        }
        
        $max_per_buy = (int) ($user['cash'] / 0.0001);
        // render portfolio
        render("buy_form.php", ["positions" => $positions, "user" => $user, "title" => "Buy", "max_per_buy" => $max_per_buy]);
    }
?>
