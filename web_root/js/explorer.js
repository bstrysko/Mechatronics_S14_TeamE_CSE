var Explorer =
{
    ws: null
};


Explorer.init = function(ip, port)
{
    var onOpen = function()
    {
        console.log("Connection opened");
    }

    Explorer.ws = new WebSocket("ws://" + ip + ":" + port);
    Explorer.ws.onOpen = onOpen;
}