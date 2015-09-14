#ifndef GOCODEPLUGIN_H
#define GOCODEPLUGIN_H

#include "process.h"
#include <ktexteditor/plugin.h>
#include <ktexteditor/view.h>
#include <ktexteditor/mainwindow.h>
#include <kxmlguiclient.h>
#include <KConfig>
#include <KPluginFactory>

class GoCodeModel;
class GoCodePluginView;

class GoCodePlugin: public KTextEditor::Plugin
{
    Q_OBJECT

public:
    GoCodePlugin(QObject *parent, const QVariantList & = QVariantList());
    ~GoCodePlugin();
    /*void addView(KTextEditor::View *view);
    void removeView(KTextEditor::View *view);*/
    QObject* createView(KTextEditor::MainWindow *mainWindow);
    virtual void readConfig(KConfig* config);
    virtual void writeConfig(KConfig* config);

private:
    Process process;
    //QMap<KTextEditor::View*, GoCodePluginView*> m_views;
};

class GoCodePluginView: public QObject, public KXMLGUIClient
{
    Q_OBJECT
public:
    //GoCodePluginView(KTextEditor::View *view, Process* process);
    GoCodePluginView(KTextEditor::MainWindow *mainWin, Process *process);
    virtual ~GoCodePluginView();

//private slots:
    //void registerCompletion();
private Q_SLOTS:
    void viewCreated(KTextEditor::View *view);
    void viewDestroyed(QObject *view);
    void documentChanged(KTextEditor::Document *document);

private:
    void registerCompletion(KTextEditor::View *view);

    GoCodeModel *m_model;
    KTextEditor::MainWindow *m_mainWindow;
    QSet<KTextEditor::View *> m_completionViews;
    //bool m_registered;
};

//K_PLUGIN_FACTORY_DECLARATION(GoCodePluginFactory)

#endif // GOCODEPLUGIN_H
