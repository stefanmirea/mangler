#include "code_container.hpp"
#include "asm_viewer.hpp"
#include "modify_asmbar.hpp"

#include <QVBoxLayout>

QWidget *CodeContainer::doSpecialRepresentation(bool &keepAfterNodeDeselection)
{
    /* create disassembly area */
    QWidget *area = new QWidget();

    ASMViewer *asmView = new ASMViewer(area);
    ModifyASMBar *modifyBar = new ModifyASMBar(area);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(asmView);
    layout->addWidget(modifyBar);

    area->setLayout(layout);

    if (canInject())
    {
        /* TODO: create Inject options in the context menu and set the injectCode
         * method to be called from inside the handler */
    }

    keepAfterNodeDeselection = true;
    return area;
}
