/** @type {import('tailwindcss').Config} */
export default {
  content: ["**/*.{html,js}"],
  theme: {
    extend: {
      keyframes: {
        smooth_bounce: {
          "0%, 100%": { transform: "translateY(0)" },
          "50%": { transform: "translateY(-20px)" },
        },
      },
      animation: {
        smooth_bounce: "smooth_bounce 6s infinite",
      },
    },
  },
  plugins: [],
};
