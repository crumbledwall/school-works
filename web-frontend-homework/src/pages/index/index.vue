<template>
  <div>
    <Nav />
    <Main />
  </div>
</template>

<script>
import Main from '../../components/Main'
import Nav from '../../components/Nav'

export default {
  name: 'index',
  components: {
    Main,
    Nav
  }
}
</script>

