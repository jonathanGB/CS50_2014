 <?php
    // configuration
        require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = htmlspecialchars($_POST['symbol']);  
        $stock = lookup($symbol);
        
        if ($stock === false)
        {
            apologize('This symbol is not valid.');
        }
        else
        {
            $stock['price'] = number_format($stock['price'], 2);
            render('quote.php', ['stock' => $stock]);
        }
        
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Lookup"]);
    }
?>
