#ifndef GOCODE_MODEL_H
#define GOCODE_MODEL_H

#include "process.h"
#include <ktexteditor/codecompletionmodel.h>
#include <ktexteditor/codecompletionmodelcontrollerinterface.h>
//#include <kicon.h>

class GoCodeModel:
    public KTextEditor::CodeCompletionModel,
    public KTextEditor::CodeCompletionModelControllerInterface
{
    Q_OBJECT
    Q_INTERFACES(KTextEditor::CodeCompletionModelControllerInterface)

public:
    GoCodeModel(QObject* parent, Process* process);
    virtual ~GoCodeModel();

    virtual void completionInvoked(KTextEditor::View* view, const KTextEditor::Range& range,
                                   InvocationType invocationType);

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    /*void executeCompletionItem2(KTextEditor::Document *document, const KTextEditor::Range &word,
                                const QModelIndex &index) const;*/

private:
    QIcon getIcon(ProcClass c) const;

    Process* m_process;
    QVector<TypeInfo> m_data;
};

#endif // GOCODE_MODEL_H
