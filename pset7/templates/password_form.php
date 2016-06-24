 <h2> Change your password </h2>
 
 <form action="password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="cur_pass" placeholder="Current password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_pass" placeholder="New password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Re-type password" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change</button>
        </div>
    </fieldset>
</form>
<br>
<div>
    <a href="logout.php">Log Out</a>
</div>

