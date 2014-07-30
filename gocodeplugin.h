#ifndef GOCODE_H
#define GOCODE_H

#include "process.h"

#include <ktexteditor/plugin.h>
#include <kxmlguiclient.h>

class GoCodeModel;
class GoCodePluginView;

class GoCodePlugin: public KTextEditor::Plugin
{
    Q_OBJECT

public:
    GoCodePlugin(QObject *parent, const QVariantList & = QVariantList());
    ~GoCodePlugin();
    void addView(KTextEditor::View *view);
    void removeView(KTextEditor::View *view);
    virtual void readConfig(KConfig* config);
    virtual void writeConfig(KConfig* config);

private:
    Process process;
    QMap<KTextEditor::View*, GoCodePluginView*> m_views;
};

class GoCodePluginView: public QObject, public KXMLGUIClient
{
    Q_OBJECT
public:
    GoCodePluginView(KTextEditor::View *view, Process* process);
    virtual ~GoCodePluginView();

private slots:
    void registerCompletion();

private:
    GoCodeModel *m_model;
    KTextEditor::View* m_view;
    bool m_registered;
};

K_PLUGIN_FACTORY_DECLARATION(GoCodePluginFactory)

#endif
