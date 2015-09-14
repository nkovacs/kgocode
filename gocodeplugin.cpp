#include "gocodeplugin.h"
#include "gocodemodel.h"

#include <kpluginfactory.h>
#include <kaboutdata.h>
#include <ktexteditor/document.h>
#include <ktexteditor/view.h>
#include <ktexteditor/codecompletioninterface.h>

/*K_PLUGIN_FACTORY(
    GoCodePluginFactory, registerPlugin<GoCodePlugin>("ktexteditor_gocode");
)*/

K_PLUGIN_FACTORY_WITH_JSON(
    GoCodePluginFactory, "ktexteditor_gocode.json", registerPlugin<GoCodePlugin>();
)

/*
K_PLUGIN_FACTORY_WITH_JSON
K_EXPORT_PLUGIN(
    GoCodePluginFactory(
        KAboutData(
            "ktexteditor_gocode",
            "ktexteditor_plugins",
            ki18n("Gocode"),
            "0.1",
            ki18n("Gocode"),
            KAboutData::License_GPL_V3,
            ki18n("Lucas Hermann Negri"),
            ki18n("Provides autocompletion for the Go language by using Gocode")
        )
    )
)
*/


GoCodePluginView::GoCodePluginView(KTextEditor::MainWindow *mainWin, Process *process):
    QObject(mainWin), m_model(new GoCodeModel(mainWin, process)),
    m_mainWindow(mainWin)
{
    /*KTextEditor::Document* document = view->document();

    connect(document, SIGNAL(documentUrlChanged(KTextEditor::Document*)),
            this, SLOT(registerCompletion()));

    connect(document, SIGNAL(highlightingModeChanged(KTextEditor::Document*)),
            this, SLOT(registerCompletion()));

    registerCompletion();*/

    connect(m_mainWindow, &KTextEditor::MainWindow::viewCreated,
        this, &GoCodePluginView::viewCreated);

    foreach(KTextEditor::View *view, m_mainWindow->views()) {
        viewCreated(view);
    }
}

void GoCodePluginView::viewCreated(KTextEditor::View *view)
{
    connect(view->document(), &KTextEditor::Document::documentUrlChanged,
        this, &GoCodePluginView::documentChanged,
        Qt::UniqueConnection);
    connect(view->document(), &KTextEditor::Document::highlightingModeChanged,
        this, &GoCodePluginView::documentChanged,
        Qt::UniqueConnection);

    registerCompletion(view);
}

void GoCodePluginView::viewDestroyed(QObject *view)
{
    m_completionViews.remove(static_cast<KTextEditor::View *>(view));
}

void GoCodePluginView::documentChanged(KTextEditor::Document *document)
{
    foreach(KTextEditor::View *view, document->views()) {
        registerCompletion(view);
    }
}

void GoCodePluginView::registerCompletion(KTextEditor::View *view)
{
    bool registered = m_completionViews.contains(view);
    bool is_go = view->document()->url().path().endsWith(QStringLiteral(".go")) ||
                 view->document()->highlightingMode() == QStringLiteral("Go");

    KTextEditor::CodeCompletionInterface *completion =
        qobject_cast<KTextEditor::CodeCompletionInterface*>(view);

    if (!completion) {
        return;
    }

    // avoid unnecessary work
    if(is_go)
    {
        if(!registered)
        {
            completion->registerCompletionModel(m_model);
            m_completionViews.insert(view);
            connect(view, &KTextEditor::View::destroyed, this,
                &GoCodePluginView::viewDestroyed,
                Qt::UniqueConnection);
        }

        return;
    }
    else
    {
        if(registered)
        {
            completion->unregisterCompletionModel(m_model);
            m_completionViews.remove(view);
        }

        return;
    }
}

/*
void GoCodePluginView::registerCompletion()
{
    KTextEditor::CodeCompletionInterface *completion =
        qobject_cast<KTextEditor::CodeCompletionInterface*>(m_view);

    bool is_go = m_view->document()->url().path().endsWith(".go") ||
                 m_view->document()->highlightingMode() == "Go";

    // avoid unnecessary work
    if(is_go)
    {
        if(!m_registered)
        {
            completion->registerCompletionModel(m_model);
            m_registered = true;
        }

        return;
    }
    else
    {
        if(m_registered)
        {
            completion->unregisterCompletionModel(m_model);
            m_registered = false;
        }

        return;
    }
}
*/

GoCodePluginView::~GoCodePluginView()
{
}

GoCodePlugin::GoCodePlugin(QObject *parent, const QVariantList &): KTextEditor::Plugin(parent)
{
}

GoCodePlugin::~GoCodePlugin()
{
}

QObject* GoCodePlugin::createView(KTextEditor::MainWindow *mainWindow)
{
    return new GoCodePluginView(mainWindow, &process);
}

/*void GoCodePlugin::addView(KTextEditor::View *view)
{
    m_views.insert(view, new GoCodePluginView(view, &process));
}*/

/*void GoCodePlugin::removeView(KTextEditor::View *view)
{
    delete m_views.take(view);
}*/



void GoCodePlugin::readConfig(KConfig *config)
{
    Q_UNUSED(config);
}

void GoCodePlugin::writeConfig(KConfig *config)
{
    Q_UNUSED(config);
}

#include "gocodeplugin.moc"
