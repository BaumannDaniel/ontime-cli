#include <memory>
#include <string>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <boost/algorithm/string.hpp>

#include "recorder_component.h"
#include "recorder_i.h"

namespace tone::ui {
    class RecorderComponentBase : public ftxui::ComponentBase {
        std::string ui_id;
        std::shared_ptr<IRecorderInfo> recorder_info;

    public:
        RecorderComponentBase(
            std::string ui_id,
            std::shared_ptr<IRecorderInfo> recorder_info
        );

        ftxui::Element Render() override;
    };
}

tone::ui::RecorderComponentBase::RecorderComponentBase(
    std::string ui_id,
    std::shared_ptr<IRecorderInfo> recorder_info
) : ui_id(std::move(ui_id)),
    recorder_info(std::move(recorder_info)) {
}

ftxui::Element tone::ui::RecorderComponentBase::Render() {
    const auto formatted_player_id = std::format("Recorder {} ", boost::to_upper_copy(ui_id));
    const auto formatted_player_file_name = std::format(" {} ", recorder_info->getFileName());
    return vbox(
               hbox(
                   ftxui::text(formatted_player_id),
                   ftxui::separator(),
                   ftxui::text(formatted_player_file_name)
               )
           ) | ftxui::border;
}

ftxui::Component tone::ui::createRecorderComponent(
    const std::string& ui_id,
    const std::shared_ptr<IRecorderInfo>& recorder_info
) {
    return ftxui::Make<RecorderComponentBase>(ui_id, recorder_info);
}