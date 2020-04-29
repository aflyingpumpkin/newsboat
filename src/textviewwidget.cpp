#include "textviewwidget.h"

#include <algorithm>

#include "utils.h"

namespace newsboat {

TextviewWidget::TextviewWidget(const std::string& textview_name,
	std::shared_ptr<Stfl::Form> form)
	: textview_name(textview_name)
	, form(form)
	, num_lines(0)
{
}

void TextviewWidget::set_lines(uint32_t number_of_lines)
{
	num_lines = number_of_lines;
}

void TextviewWidget::scroll_up()
{
	uint32_t offset = get_scroll_offset();
	if (offset > 0) {
		set_scroll_offset(offset - 1);
	}
}

void TextviewWidget::scroll_down()
{
	if (num_lines == 0) {
		// Ignore if list is empty
	}
	uint32_t maxoffset = num_lines - 1;
	uint32_t offset = get_scroll_offset();
	if (offset < maxoffset) {
		set_scroll_offset(offset + 1);
	}
}
void TextviewWidget::scroll_to_top()
{
	set_scroll_offset(0);
}

void TextviewWidget::scroll_to_bottom()
{
	if (num_lines == 0) {
		// Ignore if list is empty
	}
	uint32_t maxoffset = num_lines - 1;
	uint32_t widget_height = get_height();
	if (maxoffset + 2 < widget_height) {
		set_scroll_offset(0);
	} else {
		set_scroll_offset((maxoffset + 2) - widget_height);
	}
}

void TextviewWidget::scroll_page_up()
{
	uint32_t offset = get_scroll_offset();
	uint32_t widget_height = get_height();
	if (offset + 1 > widget_height) {
		set_scroll_offset((offset + 1) - widget_height);
	} else {
		set_scroll_offset(0);
	}
}

void TextviewWidget::scroll_page_down()
{
	if (num_lines == 0) {
		// Ignore if list is empty
	}
	uint32_t maxoffset = num_lines - 1;
	uint32_t offset = get_scroll_offset();
	uint32_t widget_height = get_height();
	if (offset + widget_height - 1 < maxoffset) {
		set_scroll_offset(offset + widget_height - 1);
	} else {
		set_scroll_offset(maxoffset);
	}
}

uint32_t TextviewWidget::get_scroll_offset()
{
	std::string offset = form->get(textview_name + "_offset");
	if (!offset.empty()) {
		return std::max(0, std::stoi(offset));
	}
	return 0;
}

void TextviewWidget::set_scroll_offset(uint32_t offset)
{
	form->set(textview_name + "_offset", std::to_string(offset));
}

uint32_t TextviewWidget::get_width()
{
	return utils::to_u(form->get(textview_name + ":w"));
}

uint32_t TextviewWidget::get_height()
{
	return utils::to_u(form->get(textview_name + ":h"));
}

} // namespace newsboat
