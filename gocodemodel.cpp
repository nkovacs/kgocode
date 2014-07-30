#include "gocodemodel.h"

#include <ktexteditor/view.h>
#include <ktexteditor/document.h>

GoCodeModel::GoCodeModel(QObject* parent, Process *process):
    CodeCompletionModel2(parent), m_process(process)
{
}

GoCodeModel::~GoCodeModel()
{

}

void GoCodeModel::completionInvoked(KTextEditor::View* view, const KTextEditor::Range& range,
                                    InvocationType invocationType)
{
    Q_UNUSED(invocationType);
    KTextEditor::Document* document = view->document();

    KTextEditor::Range r_start(KTextEditor::Cursor::start(), range.end());
    KTextEditor::Range r_end(range.end(), document->documentEnd());

    m_data = m_process->getCompletions(
                 document->text(r_start).toUtf8(),
                 document->text(r_end).toUtf8()
             );

    setRowCount(m_data.size());
    setHasGroups(false);
}

QVariant GoCodeModel::data(const QModelIndex& index, int role) const
{
    TypeInfo info = m_data[index.row()];

    switch(role)
    {
        case Qt::DecorationRole:
        {
            if(index.column() == Icon)
                return getIcon(info.class_);
            else
                return QVariant();
        }

        case Qt::DisplayRole:
        {
            switch(index.column())
            {
                case Name:
                    return info.name_;

                case Postfix:
                    return QString(" ") + info.type_;

                // falltrough
                default:
                    return QVariant();
            }
        }

        case CompletionRole:
        {
            return NoProperty;
        }

        case BestMatchesCount:
        {
            return -1;
        }

        default:
        {
            return QVariant();
        }
    }
}

#define RETURN_CACHED_ICON(name) {static QIcon icon(KIcon(name).pixmap(QSize(16, 16))); return icon;}
QIcon GoCodeModel::getIcon(ProcClass c) const
{
    switch(c)
    {
        case FUNC   :
            RETURN_CACHED_ICON("code-function");

        case VAR    :
            RETURN_CACHED_ICON("code-variable");

        case CONST  :
            RETURN_CACHED_ICON("code-variable");

        case TYPE   :
            RETURN_CACHED_ICON("code-typedef");

        case PACKAGE:
            RETURN_CACHED_ICON("code-field");

        default     :
            return KIcon();
    }
}

#include "gocodemodel.moc"
