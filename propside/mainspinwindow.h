/*
 * This file is part of the Parallax Propeller SimpleIDE development environment.
 *
 * Copyright (C) 2014 Parallax Incorporated
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * mainspinwindow.h defines main window class
 */

#ifndef MAINSPINWINDOW_H
#define MAINSPINWINDOW_H

#include "qtversion.h"

#include <QWidget>
#include <QIcon>
#include <QMainWindow>
#include <iostream>
#include <exception>
#include "stdio.h"
#include "highlighter.h"
#include "treemodel.h"
#include "PortListener.h"
#include "qextserialport.h"
#include "xesp8266port.h"
#include "terminal.h"
#include "properties.h"
#include "asideconfig.h"
#include "asideboard.h"
#include "console.h"
#include "hardware.h"
#include "projectoptions.h"
#include "cbuildtree.h"
#include "replacedialog.h"
#include "aboutdialog.h"
#include "ctags.h"
#include "newproject.h"
#include "editor.h"
#include "gdb.h"
#include "loader.h"
#include "projecttree.h"
#include "help.h"
#include "build.h"
#include "buildc.h"
#include "buildspin.h"
#include "spinparser.h"
#include "PropellerID.h"
#include "PortConnectionMonitor.h"
#include "zipper.h"
#include "StatusDialog.h"
#include "rescuedialog.h"

#ifdef QT5
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#endif

#define untitledstr "Untitled"

QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE

struct WxPortInfo {
    QString portName;   ///< Port name
    QString VendorName; ///< Vendor name
    QString ipAddr;     ///< IP Address
    QString macUpper;   ///< MAC Addr upper
    QString macAddr;    ///< MAC Address
};

//! [0]
class MainSpinWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainSpinWindow(QWidget *parent = 0);
    Properties *propDialog;
    QSize sizeHint() const;

    enum DumpType { DumpNormal, DumpReadSizes, DumpCat, DumpOff };

    void openFileName(QString fileName);
    void openFileStringTab(QString fileName, QString data);

signals:
    void highlightCurrentLine(QColor lineColor);
    void doPortEnumerate();

public slots:
    void terminalEditorTextChanged();
    void addLib();
    void addTab();
    void openTab();
    void newFile();
    void openFile(const QString &path = QString());
    void saveFile();
    void saveEditor();
    void saveFileByTabIndex(int tab);
    QStringList getAsFilters();
    QString filterAsFilename(QString name, QString filter);
    QString getSaveAsFile(const QString &path = QString());
    void saveAsFile(const QString &path = QString());
    QString getOpenAsFile(const QString &path = QString());
    void downloadSdCard();
    void printFile();
    void closeFile();
    void closeAll();
    QString getNewProjectDialog(QString workspace, QStringList filters);
    void newProject();
    void newProjectAccepted();
    void openProject(const QString &path = QString());
    void openProjectFileMatch(QString file);
    void saveProject();
    QStringList saveAsProjectNewList(QStringList projList, QString projFolder, QString projFile, QString dstPath, QString dstProjFile);
    int  copyProjectAs(QString srcProjFile, QString dstProjFile, QString mainFile);
    int  saveAsProject(const QString &path = QString());
    void cloneProject();
    void closeProject();
    void zipProject();
    void aboutShow();
    void creditShow();
    void helpShow();
    void libraryShow();
    void simpleLibraryShow();
    void referenceShow();
    void tutorialShow();
    void userguideShow();
    void projectTreeClicked();
    void closeTab(int index = 0);
    void saveTab(int index = 0, bool ask = true);
    void editorTabMenu(QPoint);
    void changeTab(bool trig);
    QStringList projectList(QString projFile);
    void currentTabChanged();
    void clearTabHighlight();
    void sdCardDownloadEnable();
    void setCurrentBoard(int index);
    void setCurrentPort(int index);
    void connectButton();
    void menuActionConnectButton();

    void portRename();
    void portResetButton();

    void resetPort(bool rts);
    void terminalClosed();
    void disablePortCombo();
    void enablePortCombo();
    void setProject();
    void hardware();
    void properties();
    void propertiesAccepted();

    void programBuildAllLibraries();
    void programStopBuild();
    void programBuild();
    void programBurnEE();
    void programRun();
    void programDebug();

    void debugCompileLoad();
    void gdbShowLine();
    void gdbKill();
    void gdbBacktrace();
    void gdbContinue();
    void gdbNext();
    void gdbStep();
    void gdbFinish();
    void gdbUntil();
    void gdbInterrupt();
    void gdbBreak();

    void compilerError(QProcess::ProcessError error);
    void compilerFinished(int exitCode, QProcess::ExitStatus status);
    void closeEvent(QCloseEvent *event);
    void clearAndExit();
    void quitProgram();

    void fileChanged();
    void keyHandler(QKeyEvent* event);
    void sendPortMessage(QString s);

    void findChip();
    QString serialPort();

    QList<WxPortInfo> getWxPorts(void);
    QString getWxPortIpAddr(QString wxname);

    void enumeratePorts();
    void enumeratePortsEvent();
    void reloadBoardTypes();
    void initBoardTypes();

    void addProjectFile();
    void addProjectLibFile();
    void addProjectLink();
    void addProjectIncPath(const QString &inpath = 0);
    void addProjectLibPath(const QString &inpath = 0);
    void deleteProjectFile();
    void showProjectFile();

    void copyFromFile();
    void cutFromFile();
    void pasteToFile();
    void editCommand();
    void systemCommand();
    void replaceInFile();
    void redoChange();
    void undoChange();
    void findDeclaration();
    void findDeclaration(QPoint point);
    void findDeclaration(QTextCursor cur);
    void prevDeclaration();
    int  showDeclaration(QString tagline);
    bool isTagged(QString text);
    void findDeclarationInfo();
    void findSymbolHelp(QString text);

    void compileStatusClicked();
    void compilerChanged();
    void showCompileStatusError();

    void procError(QProcess::ProcessError error);
    void procFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void procReadyRead();
    void procReadyReadCat();

    void wxProcReadyRead(void);
    void wxProcReadyLoad(void);
    void wxProcError(QProcess::ProcessError error);
    void wxProcFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    void openRecentFile();

    void setCurrentProject(const QString &fileName);
    void updateRecentProjectActions();
    void openRecentProject();

    void fontDialog();
    void fontBigger();
    void fontSmaller();

    void showProjectPopup();
    void showAssemblyFile();
    void showMapFile();
    int  makeDebugFiles(QString fileName);

    void toggleSimpleView();

    void showProjectPane(bool show);
    void showStatusPane(bool show);
    void splitterChanged();

    void recursiveAddDir(QString dir, QStringList *files);
    void flattenDstProject(QString path, QString project);

    void zipIt(QString dir, QString dst);
    QStringList zipCproject(QStringList list, QString srcPath, QString projFile, QString dstPath, QString dstProjFile, QString optype = tr("Zip"));
    QStringList zipSPINproject(QStringList list, QString srcPath, QString projFile, QString dstPath, QString dstProjFile);
    QString findFileNoCase(QString file);

    void statusNone();
    void statusFailed();
    void statusPassed();

    void updateWorkspace();
    void buildRescueShow();
    void enableProjectView(bool enable);

private:
    QString pathDiff(QString s2, QString s1);
    QString saveAsProjectLinkFix(QString srcPath, QString dstPath, QString link);
    int tabIndexByShortName(QString filename);
    int tabIndexByFileName(QString filename);
    void exitSave();
    void getApplicationSettings();
    int  checkCompilerInfo();
    bool isSpinProject();
    bool isCProject();
    void selectBuilder();
    QString getUnzipTempPath(QString zFile);
    int  makeBuildProjectFile(QString fileName);
    int  runBuild(QString option);
#ifdef KEEP_CTOOLS
    int  runCOGC(QString filename, QString outext);
    int  runBstc(QString spinfile);
    int  runCogObjCopy(QString datfile, QString tarfile);
    int  runObjCopyRedefineSym(QString oldsym, QString newsym, QString file);
    int  runObjCopy(QString datfile);
    int  runGAS(QString datfile);
    int  runPexMake(QString fileName);
    void removeArg(QStringList &list, QString arg);
    QStringList getCompilerParameters(QStringList options);
    int  getCompilerParameters(QStringList copts, QStringList *args);
    int  runCompiler(QStringList options);
#endif
    QStringList getLoaderParameters(QString options, QString file);
    int  runLoader(QString options);
#ifdef KEEP_CTOOLS
    int  startProgram(QString program, QString workpath, QStringList args, DumpType dump = DumpOff);
#endif
    int  startProgramTool(QString program, QString workpath, QStringList args);
    int  checkBuildStart(QProcess *proc, QString progName);
    void showBuildStart(QString progName, QStringList args);
    int  buildResult(int exitStatus, int exitCode, QString progName, QString result);

    bool isFileUTF16(QFile *file);
    void checkAndSaveFiles();
    int  setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupToolBars();
    void setupProjectTools(QSplitter *vsplit);
    void addToolButton(QToolBar *bar, QToolButton *btn, QString imgfile);
    void addToolBarAction(QToolBar *bar, QAction *btn, QString imgfile);
    bool isOutputFile(QString file);
    void addProjectListFile(QString fileName);

    void saveProjectOptions();
    void saveSpinProjectOptions();
    void saveManagedProjectOptions();

    void updateProjectTree(QString fileName);
    void updateManagedProjectTree(QString fileName, QString projName);
    void updateSpinProjectTree(QString fileName, QString projName);

    void setEditorTab(int num, QString shortName, QString fileName, QString text);
    QString shortFileName(QString fileName);
    QString sourcePath(QString file);

    void cStatusClicked(QString line);
    void spinStatusClicked(QString line);

    void resetVerticalSplitSize();
    void resetRightSplitSize();

    void showSimpleView(bool simple);

    bool rtsReset();
    void resizeEvent(QResizeEvent *ev);

    AboutDialog     *aboutDialog;
    QString         aboutLanding;

    Help            *helpDialog;

    QSettings       *settings;
    QString         aSideLoader;
    QString         aSideCompiler;
    QString         aSideCompilerPath;
    QString         aSideIncludes;
    QString         aSideCfgFile;
    QString         aSideSeparator;
    QString         aSideDocPath;
    bool            simpleViewType;

    QIcon           simpleViewIcon;
    QIcon           projectViewIcon;

    QToolBar        *fileToolBar;
    QToolBar        *projToolBar;
    QToolBar        *propToolBar;
    QToolBar        *browseToolBar;
    QToolBar        *programToolBar;
    QToolBar        *ctrlToolBar;
    QToolBar        *boardToolBar;
    QToolBar        *addToolsToolBar;
    QToolBar        *sdCardToolBar;
    QToolBar        *resetToolBar;

    QMenu           *fileMenu;
    QMenu           *projMenu;
    QMenu           *toolsMenu;
    QMenu           *programMenu;

    QSplitter       *vsplit;
    QSplitter       *leftSplit;
    QSplitter       *rightSplit;

    QAction         *btnProjectAddTab;
    QAction         *btnProjectAddLib;
    QAction         *btnProjectOpenTab;

    QAction         *btnBoardReset;
    QAction         *btnProjectClose;
    QAction         *btnLoadBoards;
    QPushButton     *btnShowProjectPane;
    QPushButton     *btnShowStatusPane;

    QAction         *btnPortScan;

    QTabWidget      *editorTabs;
    QVector<Editor*> *editors;
    QFont           editorFont;
    bool            fileChangeDisable;
    bool            tabChangeDisable;
    QMenu           *edpopup;

    QPlainTextEdit  *compileStatus;
    bool            compileStatusClickEnable;

    QString         projectFile;
    CBuildTree      *projectModel;
    ProjectTree     *projectTree;
    CBuildTree      *referenceModel;
#ifdef REFERENCE_TREE
    QTreeView       *referenceTree;
#endif
    QString         basicPath;
    QString         includePath;

    QFileDialog     fileDialog;

    QComboBox       *cbBoard;
    QComboBox       *cbPort;
    QStringList     friendlyPortName;
    QAction         *btnConnected;
    QToolButton     *btnDownloadSdCard;

#if defined(LOADER_TERMINAL)
    Loader          *termEditor;
#else
    Console         *termEditor;
#endif

    PortListener    *portListener;
    Terminal        *term;

    int             termXpos;
    int             termYpos;

    ASideConfig     *aSideConfig;
    QString         portName;
    QString         boardName;

    QProcess        *process;
    QProgressBar    *progress;
    int             progMax;
    int             progCount;
    bool            procDone;
    bool            procResultError;
    QMutex          procMutex;

    Hardware        *hardwareDialog;
    QLabel          *status;
    QLabel          *programSize;

    QMenu           *projectMenu;
    QString         projectHome;

    ProjectOptions  *projectOptions;

    // find and replace
    ReplaceDialog   *replaceDialog;

    enum { MaxRecentFiles = 10 };
    QAction *recentFileActs[MaxRecentFiles];
    QAction *separatorFileAct;

    enum { MaxRecentProjects = 10 };
    QAction *recentProjectActs[MaxRecentProjects];
    QAction *separatorProjectAct;

    CTags           *ctags;
    QToolButton     *btnBrowseBack;
    QToolButton     *btnFindDef;
    NewProject      *newProjDialog;

    QString         lastPath;

    QTabWidget      *statusTabs;
    GDB             *gdb;
    QPlainTextEdit  *gdbStatus;
    QPlainTextEdit  *toolStatus;

    QToolButton *btnProgramDebugTerm;
    QToolButton *btnProgramRun;

    Build           *builder;
    BuildC          *buildC;
    BuildSpin       *buildSpin;
    SpinParser      spinParser;

    Blinker         *blinker;

    PropellerID     propId;

    PortConnectionMonitor *portConnectionMonitor;

    StatusDialog    *statusDialog;
    Zipper          zipper;

    bool            allowProjectView;

    RescueDialog    *rescueDialog;

    QString         lastCbPort;
    QPrinter        printer;

    QList<WxPortInfo> wxPorts;
    QProcess        *wxProcess;
    QString         wxPortString;

public slots:
    void ideDebugShow();
private:
    int ideDebugTabIndex;

};

//! [0]

// Macro which connects a signal to a slot, and which causes application to
// abort if the connection fails.  This is intended to catch programming errors
// such as mis-typing a signal or slot name.  It is necessary to write our own
// macro to do this - the following idiom
//     Q_ASSERT(connect(source, signal, receiver, slot));
// will not work because Q_ASSERT compiles to a no-op in release builds.

#define CHECKED_CONNECT(source, signal, receiver, slot) \
    if(!connect(source, signal, receiver, slot)) \
        qt_assert_x(Q_FUNC_INFO, "CHECKED_CONNECT failed", __FILE__, __LINE__);

#endif
