const net = require("net");

const server = net.createServer((socket) => {
  console.log("Client connected:", socket.remoteAddress, socket.remotePort);

  socket.on("data", (data) => {
    const msg = data.toString().trim();
    console.log("RX:", msg);

    // 예시: 받은 메시지에 대한 응답 / Example: Respond to received message
    socket.write("ACK:" + msg + "\n");
  });

  socket.on("end", () => {
    console.log("Client disconnected");
  });

  socket.on("error", (err) => {
    console.error("Socket error:", err);
  });
});

server.listen(3000, "192.168.0.100", () => {
  console.log("TCP server listening on 192.168.0.100:3000");
});
