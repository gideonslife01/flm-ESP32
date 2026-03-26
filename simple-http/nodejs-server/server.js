const express = require("express");
const app = express();
app.use(express.json());

// Node 18+는 fetch 내장
const esp32Ip = "192.168.0.100"; // YOUR ESP32 IP ADDRESS

app.post("/sensor", (req, res) => {
  console.log("sensor data:", req.body);
  res.json({ ok: true });
});

// app.post("/control", (req, res) => {
//   console.log("control:", req.body);
//   res.json({ ok: true });
// });


app.get("/control", async (req, res) => {
  console.log("control:", req.query); 
  try {
    const r = await fetch(`http://${esp32Ip}/control?led=${req.query.led}`);
    const text = await r.text();
    res.json({ ok: true, esp32: text });
  } catch (err) {
    console.error(err);
    res.status(500).json({ ok: false, error: String(err) });
  }
});


app.get("/", (req, res) => {
  res.send("Server OK");
});

app.listen(3000, () => {
  console.log("Server running on http://192.168.0.100:3000");
});

