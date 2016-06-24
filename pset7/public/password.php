<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $user = query("SELECT hash FROM users WHERE id = ?", $_SESSION['id']);
        $user = $user[0];
    
        $cur_pass = $_POST['cur_pass'];
        $new_pass = $_POST['new_pass'];
        $confirmation = $_POST['confirmation'];
        
        if (empty($cur_pass))
        {
            apologize('You must enter your current password.');
        }
        else if (crypt($cur_pass, $user['hash']) != $user["hash"])
        {
            apologize('The current password is invalid.');
        }
        else if (empty($new_pass) || empty($confirmation))
        {
            apologize('The new password and/or the confirmation is empty.');
        }
        else if($new_pass != $confirmation)
        {
            apologize('The new password and the confirmation must be the same.');
        }
        
        $change_pass = query("UPDATE users SET hash = ?", crypt($new_pass));
        
        render("password.php", ["title" => "Successful"]);
    }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Change password"]);
    }

?>
