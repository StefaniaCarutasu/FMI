import { useContext } from 'react'
import {ThemeContext} from '../context/ThemeContext'

export const useTheme = () => {
    const context = useContext(ThemeContext);

    if (context === undefined) {
        throw new Error("useTheme() must be use inside a ThemeProvider")
    }

    return context;
}