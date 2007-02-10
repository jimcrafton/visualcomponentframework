function onRunning(e) 
{
  PrintMe.print("js event handler onRunning() called!");
}

function onStateChanged(e) 
{
  PrintMe.print("js event handler onStateChanged() called!");
}

var hermes = new HermesTheFleet();

hermes.StateChanged = onStateChanged;
hermes.RunningLaps = onRunning;
hermes.numLaps = 10;
hermes.running = true;