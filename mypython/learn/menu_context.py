import wx

class MyPopupMenu(wx.Menu):
    
    def __init__(self, parent):
        super(MyPopupMenu, self).__init__()
        self.parent = parent

        mmi = wx.MenuItem(self, wx.NewId(), 'Minimize')
        self.AppendItem(mmi)
        self.Bind(wx.EVT_MENU, self.OnMinimize, mmi)

        cmi = wx.MenuItem(self, wx.NewId(), 'Close')
        self.AppendItem(cmi)
        self.Bind(wx.EVT_MENU, self.OnClose, cmi)

    def OnMinimize(self, e):
        self.parent.Iconize()

    def OnClose(self, e):
        self.parent.Close()
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 500), pos = (0, 0))
        self.InitUi()
        
    def InitUi(self):
        menubar1 = wx.MenuBar()
        fileMenu = wx.Menu()
        viewMenu = wx.Menu()

        self.shst = viewMenu.Append(wx.ID_ANY, 'Show statubar', 
            'Show Statusbar', kind=wx.ITEM_CHECK)
        self.shtl = viewMenu.Append(wx.ID_ANY, 'Show toolbar', 
            'Show Toolbar', kind=wx.ITEM_CHECK)

        self.Bind(wx.EVT_MENU, self.ToggleStatusBar, self.shst)
        self.Bind(wx.EVT_MENU, self.ToggleToolBar, self.shtl)

        self.toolbar = self.CreateToolBar()
        self.toolbar.Realize()

        self.statusbar = self.CreateStatusBar()
        self.statusbar.SetStatusText('Ready')

        fileMenu.Append(wx.ID_NEW, '&New')
        fileMenu.Append(wx.ID_SAVE, '&Save')
        fileMenu.AppendSeparator()

        imp = wx.Menu()
        imp.Append(wx.ID_ANY, 'Import newsfeed list...')
        imp.Append(wx.ID_ANY, 'Import mail...')

        fileMenu.AppendMenu(wx.ID_ANY, 'I&mport', imp)

        qmi = wx.MenuItem(fileMenu, wx.ID_EXIT, '&Quit\tCtrl+W')
        fileMenu.AppendItem(qmi)

        self.Bind(wx.EVT_MENU, self.OnQuit, qmi)

        menubar1.Append(fileMenu, '&File1')
        menubar1.Append(viewMenu, '&View')
        self.SetMenuBar(menubar1)
        
        self.Bind(wx.EVT_MENU, self.OnQuit, qmi)
        
        #bind a right click event
        self.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown)

    def OnRightDown(self, e):
        self.PopupMenu(MyPopupMenu(self), e.GetPosition())

        
    def ToggleStatusBar(self, e):
        
        if self.shst.IsChecked():
            self.statusbar.Show()
        else:
            self.statusbar.Hide()

    def ToggleToolBar(self, e):
        
        if self.shtl.IsChecked():
            self.toolbar.Show()
        else:
            self.toolbar.Hide()
            
    def OnQuit(self, e):
        self.Close()

    
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
