 <?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $username = htmlspecialchars($_POST['username']);
        $password = htmlspecialchars($_POST['password']);
        $confirmation = htmlspecialchars($_POST['confirmation']);
        
        if (empty($username))
        {
            apologize('You must enter a username.');
        }
        else if(empty($password))
        {
            apologize('You must enter a password.');
        }
        else if($password != $confirmation)
        {
            apologize('The password and the confirmation should be the same.');
        }
        
        $valid_username = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $username, crypt($password));
        if($valid_username === false)
        {
            apologize('This username is already taken, please choose another one.');
        }
        else
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]['id'];
            
            $_SESSION['id'] = $id;
            redirect('index.php');
        }  
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
