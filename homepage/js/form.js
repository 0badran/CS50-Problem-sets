(() => {
    const forms = document.querySelectorAll(".needs-validation");
    Array.from(forms).forEach((form) => {
        form.addEventListener("submit", (event) => {
            event.preventDefault();
            event.stopPropagation();
            form.classList.add("was-validated");
            const userName = document.getElementById("validationCustomUsername");
            if (form.checkValidity()) {
                sessionStorage.setItem("user", userName.value);
                location.href = '/';
            }

        }, false);
    });
})();