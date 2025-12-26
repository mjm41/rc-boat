const ESP_HOST = "192.168.4.1";
var connection = new WebSocket(`ws://${ESP_HOST}:81/`, ['arduino']);

connection.onopen = function () 
{
    connection.send('Connect ' + new Date());
};


connection.onerror = function (error) 
{
    console.log('WebSocket Error ', error);
};


connection.onmessage = function (e) 
{
    console.log('Server: ', e.data);
};


connection.onclose = function () 
{
    console.log('WebSocket connection closed');
};


function axisTo255(a) {
  return Math.round((Math.max(-1, Math.min(1, a)) + 1) * 127.5);
}

function axisTo180(a) {
  return Math.round((Math.max(-1, Math.min(1, a)) + 1) * 90);
}


function loopGamepad() {
  const gp = navigator.getGamepads()[0];
  if (gp) 
  {
    const y = -(gp.axes[3] || 0);          // common right-stick Y
    const x = gp.axes[2] || 0);
    const vy = axisTo255(y);             // 0..255, center ~128
    const vx = axisTo180(x);             // 0..180, center ~90
    document.getElementById('thrust').value = vy;
    document.getElementById('direction').value = vx;
    if (connection.readyState === WebSocket.OPEN)
    {
      connection.send(`Y:${vy}`);
      connection.send(`X:${vx}`);
    }
  }
  requestAnimationFrame(loopGamepad);
}

requestAnimationFrame(loopGamepad);


/*
function sendDirection () 
{
    // TODO
}
*/
