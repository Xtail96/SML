import { app, BrowserWindow } from "electron";
import * as path from "path";
const electronLocalshortcut = require('electron-localshortcut');
import yargs = require('yargs');

let mainWindow: Electron.BrowserWindow;

function createWindow(gcodesFilePath: string | undefined = undefined) {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      nodeIntegration: true
    },
    width: 800,
  });

  // and load the index.html of the app.
  mainWindow.loadFile(path.join(__dirname, "webVisualizer", "index.html"));

  // Open the DevTools.
  electronLocalshortcut.register(mainWindow, 'Ctrl+Shift+I', () => { mainWindow.webContents.openDevTools(); });

  mainWindow.webContents.once('dom-ready', () => {
    mainWindow.webContents.send('show-gcodes', gcodesFilePath);
  });

  // Emitted when the window is closed.
  mainWindow.on("closed", () => {
    // Dereference the window object, usually you would store windows
    // in an array if your app supports multi windows, this is the time
    // when you should delete the corresponding element.
    mainWindow = null;
  });
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on("ready", () => {
  let argv = yargs.argv;

  let gcodesFilePath: string | undefined = undefined;
  if(typeof(argv.f) == "string") gcodesFilePath = argv.f;

  createWindow(gcodesFilePath);
});

// Quit when all windows are closed.
app.on("window-all-closed", () => {
  app.quit();
});

app.on("activate", () => {
  // On OS X it"s common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (mainWindow === null) {
    createWindow();
  }
});

// In this file you can include the rest of your app"s specific main process
// code. You can also put them in separate files and require them here.