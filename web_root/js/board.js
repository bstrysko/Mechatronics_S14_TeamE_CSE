var Board =
{
    cols: 9,
    rows: 9
};

Board.init = function()
{
    var board = "<table class='table table-bordered'>";

    for(var y = 0; y < Board.rows; y++)
    {
        board += "<tr>";

        for(var x = 0; x < Board.cols; x++)
        {
            board += "<td id='board" + (y*Board.rows + x) + "' class='tile tile-unknown'>";
            board += "</td>";
        }

        board += "</tr>";
    }

    board += "</table>";

    $("#board").html(board);

    console.log("Board initialized");
}

Board.setSquareState = function(n, defect)
{
    var square = $("#board" + n);
    square.removeClass("tile-unknown tile-ndefect tile-defect");
    square.addClass(defect ? "tile-defect" : "tile-ndefect");

    console.log("Square " + n + "set to " + defect);
}