<?php
    // configuration
    require("../includes/config.php");
    
    $positions = [];
    $user = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION['id']);
    $user = $user[0];
    $history_rows = query("SELECT transaction, name, symbol, amount, price, time FROM history WHERE user_id = ? ORDER BY time DESC",
                           $_SESSION['id']);
    
    foreach ($history_rows as $history_row)
    {
        if ($history_row['transaction'] == 'Buy')
            $colour = 'red';
        else
            $colour = 'green';
            
        $positions[] = [
            "transaction" => $history_row['transaction'],
            "name" => $history_row["name"],
            "price" => $history_row["price"],
            "shares" => $history_row["amount"],
            "symbol" => $history_row["symbol"],
            "cash_variation" => $history_row["amount"] * $history_row["price"],
            "time" => $history_row['time'],
            "colour" => $colour,
        ];     
    }

    // render portfolio
    render("history.php", ["positions" => $positions, "user" => $user, "title" => "History"]);
?>
