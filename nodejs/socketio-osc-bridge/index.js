const http = require('http');
const { Client, Bundle } = require('node-osc');
const osc = require('node-osc');
const socket = require('socket.io');

let osc_host = '192.168.1.66'; //'10.10.10.140';
let osc_port = 9000;
let socket_port = 3000;

let app = http.createServer();
let io = socket(app);
app.listen(socket_port);

let osc_client = new Client(osc_host, osc_port);

let connected = false;

console.log("listening on " + socket_port);

io.on('connection', (socket) => {
   console.log('a socket connected');

   socket.on("draw", (json) => {
      let data = JSON.parse(json);
      // console.log(data);
      osc_client.send(new Bundle(
         ['/X', data.X],
         ['/Y', data.Y],
         ['/R', data.R],
         ['/G', data.G],
         ['/B', data.B]
         ));
   });

   socket.on("clear", () => {
      osc_client.send('/clear');
   });

   socket.on('disconnect', () => {
      if (connected) {
         osc_client.kill();
      }
   });

});
