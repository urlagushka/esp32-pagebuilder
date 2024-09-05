#include "stylesheet.hpp"

const std::string kb::get_style()
{
    return R"STYLE(
        body
        {
            font-family: "Trebuchet MS";
        }

        .block
        {
            width: 400px;
            min-height: 150px;
            border: 2px solid black;
            box-shadow: 2px 2px 4px rgba(0, 0, 0, 0.4);
            display: flex;
            flex-flow: column;
            height: 100%;
        }

        .top
        {
            background-color: #1E90FF;
            border-bottom: 1px solid black;
            flex: 0 1 auto;
            padding-left: 10px;
            font-size: 24px;
            font-weight: bold;
        }

        .mid
        {
            background-color: #F5F5F5;
            flex: 1 1 auto;
            padding-left: 10px;
        }

        .bot
        {
            background-color: #FFFAFA;
            border-top: 1px solid black;
            height: 20px;
            padding-left: 10px;
            padding-top: 2px;
        }

        .grid
        {
            display: flex;
            flex-wrap: wrap;
            justify-content: left;
            gap: 10px;
        }

        input[type=text]
        {
            width: 65%;
            padding: 5px 10px;
            box-sizing: border-box;
        }

        .btn
        {
            width: 30%;
            padding: 5px 10px;
            font-size: 14px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            outline: none;
            background-color: #e9f4f7;
            border: 1px solid black;
        }

        .btn:hover
        {
            background-color: lightblue;
        }

        .btn:active
        {
            background-color: #77d4e4;
        }

        .btns
        {
            width: 96%;
            padding: 5px 10px;
            font-size: 14px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            outline: none;
            background-color: #e9f4f7;
            border: 1px solid black;
        }

        .btns:hover
        {
            background-color: lightblue;
        }

        .btns:active
        {
            background-color: #77d4e4;
        }

    )STYLE";
}
