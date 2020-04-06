import { app, BrowserWindow, ipcMain } from "electron";
import * as path from "path";
const electronLocalshortcut = require('electron-localshortcut');
import yargs = require('yargs');
import { Repository } from "./repository";


let mainWindow: Electron.BrowserWindow;
let repository: Repository = new Repository();

function createWindow() {
  mainWindow = new BrowserWindow({
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      nodeIntegration: true
    },
    width: 800,
    show: false
  });

  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
  });

  mainWindow.loadFile(path.join(__dirname, "webVisualizer", "index.html"));
  electronLocalshortcut.register(mainWindow, 'Ctrl+Shift+I', () => { mainWindow.webContents.openDevTools(); });

  mainWindow.on("closed", () => {
    mainWindow = null;
  });
}

app.on("ready", () => {
  let argv = yargs.argv;

  let gcodesFilePath: string | undefined = undefined;
  if(typeof(argv.f) == "string") gcodesFilePath = argv.f;
  repository.setGCodesFilePath(gcodesFilePath);

  createWindow();
});

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

ipcMain.on('getGCodesFilePath', (event: any) => {
  event.returnValue = repository.gcodesFilePath();
});
