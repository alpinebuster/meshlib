#pragma once

#include "config.h"
#ifndef MRIOEXTRAS_NO_PDF
#include "exports.h"

#include <filesystem>
#include <vector>

namespace MR
{

/**
 * @brief Parameters of document style
 */
struct PdfParameters
{
    float titleSize = 18.f;
    float textSize = 14.f;
    /**
     * @brief Font name
     * list of available fonts:
     * Courier (-Bold, -Oblique, -BoldOblique)
     * Helvetica (-Bold, -Oblique, -BoldOblique)
     * Times (-Roman, -Bold, -Italic, -BoldItalic)
     * Symbol
     * ZapfDingbats
     */
    std::string fontName = "Helvetica";
};

/**
 * Class for simple creation pdf.
 */
class Pdf
{
public:
    /// Ctor
    MRIOEXTRAS_API Pdf( const std::filesystem::path& documentPath, const PdfParameters& params = PdfParameters() );
    MRIOEXTRAS_API Pdf( Pdf&& other ) noexcept;
    MRIOEXTRAS_API Pdf& operator=( Pdf other ) noexcept; // Sic, passing by value.
    /// Dtor. Automatically do close
    MRIOEXTRAS_API ~Pdf();

    Pdf( const Pdf& rhs ) = delete;
    Pdf& operator = ( const Pdf& rhs ) = delete;

    /**
     * Add text block in current cursor position.
     * Move cursor.
     * Box horizontal size is page width without offset.
     * Box vertical size is automatically for text.
     * horAlignment = left
     * if isTitle - horAlignment = center, use titleFontSize
     */
    MRIOEXTRAS_API void addText( const std::string& text, bool isTitle = false );

    /**
     * @brief Add image from file in current cursor position.
     * If image bigger than page size, autoscale image to page size.
     * Move cursor.
     * @param valuesMarks if not empty - add marks under image.
     * valuesMarks contains pairs<relative_position, marks_text>.
     *     relative_position is in range [0., 1.], where 0. - left border of image, 1. - right border
     * @param caption if not empty - add caption under marks (if exist) or image.
     */
    MRIOEXTRAS_API void addImageFromFile( const std::filesystem::path& imagePath, const std::string& caption = {},
        const std::vector<std::pair<double, std::string>>& valuesMarks = {} );

    /// Add new pageand move cursor on it
    MRIOEXTRAS_API void newPage();

    /// Save and close document. After this impossible add anything in document
    MRIOEXTRAS_API void close();

    void setCursorPosX( float posX ) { cursorX_ = posX; }
    void setCursorPosY( float posY ) { cursorY_ = posY; }
    float getCursorPosX() const { return cursorX_; }
    float getCursorPosY() const { return cursorY_; }

    /// Checking the ability to work with a document
    MRIOEXTRAS_API operator bool() const;

private:
    struct State;
    std::unique_ptr<State> state_;

    std::filesystem::path filename_;

    PdfParameters params_;

    float cursorX_ = 0;
    float cursorY_ = 0;

    bool checkDocument() const;
};

}
#endif
