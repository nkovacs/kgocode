#ifndef GOCODE_MODEL_H
#define GOCODE_MODEL_H

#include "process.h"
#include <ktexteditor/codecompletionmodel.h>
#include <ktexteditor/codecompletionmodelcontrollerinterface.h>
#include <kicon.h>

class GoCodeModel:
    public KTextEditor::CodeCompletionModel2,
    public KTextEditor::CodeCompletionModelControllerInterface3
{
    Q_OBJECT
    Q_INTERFACES(KTextEditor::CodeCompletionModelControllerInterface3)

public:
    GoCodeModel(QObject* parent, Process* process);
    virtual ~GoCodeModel();

    virtual void completionInvoked(KTextEditor::View* view, const KTextEditor::Range& range,
                                   InvocationType invocationType);

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    QIcon getIcon(ProcClass c) const;

    Process* m_process;
    QVector<TypeInfo> m_data;
};

#endif // GOCODE_MODEL_H
