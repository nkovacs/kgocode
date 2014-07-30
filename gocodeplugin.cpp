#include "gocodeplugin.h"
#include "gocodemodel.h"

#include <kpluginfactory.h>
#include <kaboutdata.h>
#include <ktexteditor/document.h>
#include <ktexteditor/view.h>
#include <ktexteditor/codecompletioninterface.h>

K_PLUGIN_FACTORY_DEFINITION(
    GoCodePluginFactory, registerPlugin<GoCodePlugin>("ktexteditor_gocode");
)

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

GoCodePluginView::GoCodePluginView(KTextEditor::View *view, Process *process):
    QObject(view), KXMLGUIClient(view), m_model(new GoCodeModel(view, process)),
    m_view(view), m_registered(false)
{
    KTextEditor::Document* document = view->document();

    connect(document, SIGNAL(documentUrlChanged(KTextEditor::Document*)),
            this, SLOT(registerCompletion()));

    connect(document, SIGNAL(highlightingModeChanged(KTextEditor::Document*)),
            this, SLOT(registerCompletion()));

    registerCompletion();
}

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

GoCodePluginView::~GoCodePluginView()
{
}

GoCodePlugin::GoCodePlugin(QObject *parent, const QVariantList &): KTextEditor::Plugin(parent)
{
}

GoCodePlugin::~GoCodePlugin()
{
}

void GoCodePlugin::addView(KTextEditor::View *view)
{
    m_views.insert(view, new GoCodePluginView(view, &process));
}

void GoCodePlugin::removeView(KTextEditor::View *view)
{
    delete m_views.take(view);
}

void GoCodePlugin::readConfig(KConfig *config)
{
    Q_UNUSED(config);
}

void GoCodePlugin::writeConfig(KConfig *config)
{
    Q_UNUSED(config);
}

#include "gocodeplugin.moc"
